﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NUnit.Framework;
using FX3Api;
using System.IO;
using System.Reflection;
using RegMapClasses;

namespace iSensor_SPI_Buffer_Test
{
    class BufferTests : TestBase
    {
        [Test]
        public void BufferRetrieveTimeTest()
        {
            InitializeTestCase();
        }

        [Test]
        public void BufferClearTest()
        {
            InitializeTestCase();
        }

        [Test]
        public void BufferLenTest()
        {
            InitializeTestCase();
        }

        [Test]
        public void BufferTimestampTest()
        {
            InitializeTestCase();
        }

        [Test]
        public void BufferCountTest()
        {
            InitializeTestCase();
        }

        [Test]
        public void BufferSettingsTest()
        {
            InitializeTestCase();

            /* Mode, overflow behavior, SPI word size */
        }

        [Test]
        public void BufferMaxDataRateTest()
        {
            InitializeTestCase();

            uint index;

            double freq;

            /* Set writedata regs */
            index = 1;
            foreach(RegClass reg in WriteDataRegs)
            {
                Dut.WriteUnsigned(reg, index);
                index++;
            }

            /* Fast IMU SPI config (9MHz SCLK, 2us stall) */
            WriteUnsigned("IMU_SPI_CONFIG", 0x202, true);

            Console.WriteLine("Testing buffer max data rate with no user SPI traffic and smallest buffer size...");
            WriteUnsigned("BUF_LEN", 2, true);
            CheckDUTConnection();
            freq = FindMaxDrFreq(2, 200.0, 100.0);
            Assert.GreaterOrEqual(freq, 5000, "ERROR: Max supported DR freq must be at least 5KHz...");

            FX3.StallTime = 100;
            Console.WriteLine("Testing buffer max data rate with no user SPI traffic and largest buffer size...");
            WriteUnsigned("BUF_LEN", 64, true);
            freq = FindMaxDrFreq(64, 50.0, 50.0);
            /* 64 bytes of SPI traffic + 32 2us stall times -> ~128us best case without burst read */
            Assert.GreaterOrEqual(freq, 1000, "ERROR: Max supported DR freq must be at least 1KHz...");
        }

        private double FindMaxDrFreq(int bufSize, double startFreq, double freqStep)
        {
            double freq = startFreq;
            double timestampfreq, avgFreq;
            bool goodFreq = true;
            int numSamples = 100;
            int numAverages;

            uint[] bufData;

            while(goodFreq)
            {
                Console.WriteLine("Testing data ready freq of " + freq.ToString() + "Hz");
                /* Flush buffer */
                WriteUnsigned("USER_COMMAND", 1 << COMMAND_CLEAR_BUFFER, false);
                System.Threading.Thread.Sleep(10);
                /* Put DUT on correct page */
                ReadUnsigned("BUF_TIMESTAMP_LWR");
                FX3.StartPWM(freq, 0.5, FX3.DIO1);
                /* Wait for numSamples samples to be enqueued */
                System.Threading.Thread.Sleep((int) (1500 * numSamples / freq));
                /* Stop clock */
                FX3.StopPWM(FX3.DIO1);
                Console.WriteLine("Status: 0x" + ReadUnsigned("STATUS").ToString("X4"));
                if(ReadUnsigned("BUF_CNT") < numSamples)
                {
                    Console.WriteLine("ERROR: Less samples enqueued than expected: " + ReadUnsigned("BUF_CNT").ToString());
                    goodFreq = false;
                }
                bufData = Dut.ReadUnsigned(10, ReadDataRegs, 1, (uint) numSamples);
                long timeStamp, oldTimestamp;
                oldTimestamp = bufData[1];
                oldTimestamp += (bufData[2] << 16);
                int index = ReadDataRegs.Count;
                avgFreq = 0;
                numAverages = 0;
                for(int j = 1; j < numSamples; j++)
                {
                    if (bufData[index] != 0)
                        goodFreq = false;
                    timeStamp = bufData[index + 1];
                    timeStamp += (bufData[index + 2] << 16);
                    index += 3;
                    for (int i = 3; i < ReadDataRegs.Count; i++)
                    {
                        if((i - 3) < (bufSize / 2))
                        {
                            if (bufData[index] != (i - 2))
                            {
                                goodFreq = false;
                            }
                        }
                        else
                        {
                            if (bufData[index] != 0)
                            {
                                goodFreq = false;
                            }
                        }
                        index++;
                    }
                    //Console.WriteLine("Timestamp: " + timeStamp.ToString());
                    timestampfreq = (1000000.0 / (timeStamp - oldTimestamp));
                    avgFreq += timestampfreq;
                    numAverages++;
                    oldTimestamp = timeStamp;
                }

                avgFreq = avgFreq / numAverages;
                Console.WriteLine("Average sample freq (from timestamp): " + avgFreq.ToString("f2") + "Hz");
                /* If average timestamp error of more than 2% then is bad */
                if (((freq - avgFreq) / freq) > 0.02)
                    goodFreq = false;

                if (goodFreq)
                    freq += freqStep;
            }
            return freq;
        }



    }
}
