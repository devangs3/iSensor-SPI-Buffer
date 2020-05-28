﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NUnit.Framework;
using FX3Api;
using System.IO;
using System.Reflection;

namespace iSensor_SPI_Buffer_Test
{
    class PinTests : TestBase
    {
        [Test]
        public void DrPinAssignmentTest()
        {
            InitializeTestCase();
        }

        [Test]
        public void DrPolarityTest()
        {
            InitializeTestCase();
        }

        [Test]
        public void DIOConfigTest()
        {
            InitializeTestCase();
        }

        [Test]
        public void OverflowInterruptTest()
        {
            InitializeTestCase();
        }

        [Test]
        public void WatermarkInterruptTest()
        {
            InitializeTestCase();
        }

    }
}
