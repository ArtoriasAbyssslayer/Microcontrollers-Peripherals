#!/usr/bin/python
from redBlocks import *
from redBlocksTest import *


scf = SimulatorConnectionFactory()

# Registration of interfaces
scf.registerDO("Product 4 Lamp")
scf.registerDO("Product 3 Lamp")
scf.registerDO("Product 2 Lamp")
scf.registerDO("Product 1 Lamp")
scf.registerDO("Dispense Bay Lamp")
scf.registerDO("Change Bay Lamp")
scf.registerDO("Open Cash Box Actor")
scf.registerDO("Cash Box Return Actor")
scf.registerDO("Product 1 Release Gear")
scf.registerDO("Product 2 Release Gear")
scf.registerDO("Product 3 Release Gear")
scf.registerDO("Product 4 Release Gear")
scf.registerCC("GSM Modem")
scf.registerDP("Display")
scf.registerSBO("Euro200")
scf.registerSBO("EnableCoolingSystem")
sc = scf.create()

# Define set of interfaces to observe
observer = Observer()
observer.add(sc.DO("Product 4 Lamp"))
observer.add(sc.DO("Product 3 Lamp"))
observer.add(sc.DO("Product 2 Lamp"))
observer.add(sc.DO("Product 1 Lamp"))
observer.add(sc.DO("Dispense Bay Lamp"))
observer.add(sc.DO("Change Bay Lamp"))
observer.add(sc.DO("Open Cash Box Actor"))
observer.add(sc.DO("Cash Box Return Actor"))
observer.add(sc.DO("Product 1 Release Gear"))
observer.add(sc.DO("Product 2 Release Gear"))
observer.add(sc.DO("Product 3 Release Gear"))
observer.add(sc.DO("Product 4 Release Gear"))
observer.add(sc.CC("GSM Modem"), 0.10)
observer.add(sc.DP("Display"), 0.10)

# time tolerance: adjust to a suitable value depending on the latency of the test setup
TOL = 0.20
observer.setTolerance(TOL)

observer.start()
time = observer.getTime()


# Test Preconditions
observer[sc.DO("Product 4 Lamp")].checkData(False)
observer[sc.DO("Product 3 Lamp")].checkData(False)
observer[sc.DO("Product 2 Lamp")].checkData(False)
observer[sc.DO("Product 1 Lamp")].checkData(False)
observer[sc.DO("Dispense Bay Lamp")].checkData(False)
observer[sc.DO("Change Bay Lamp")].checkData(False)
observer[sc.DO("Open Cash Box Actor")].checkData(False)
observer[sc.DO("Cash Box Return Actor")].checkData(False)
observer[sc.DO("Product 1 Release Gear")].checkData(False)
observer[sc.DO("Product 2 Release Gear")].checkData(False)
observer[sc.DO("Product 3 Release Gear")].checkData(False)
observer[sc.DO("Product 4 Release Gear")].checkData(False)
observer[sc.DP("Display")].checkData(DisplayData.fromFileContents(binaryData("0.rbb")))

observer.sleep(3.290)

time = observer.getTime()
sc.SBO("Euro200").setValue(True)

observer.sleep(0.812)

time = observer.getTime()
sc.SBO("Euro200").setValue(False)

observer.sleep(0.643)

time = observer.getTime()
sc.SBO("Euro200").setValue(True)

observer.sleep(0.162)

time = observer.getTime()
sc.SBO("Euro200").setValue(False)

observer.sleep(4.298)

time = observer.getTime()
sc.SBO("EnableCoolingSystem").setValue(True)

observer.sleep(3.694)

time = observer.getTime()
sc.SBO("Euro200").setValue(True)

observer.sleep(0.542)

time = observer.getTime()
sc.SBO("Euro200").setValue(False)

observer.sleep(16.059 + TOL)

time = observer.getTime()

# Test end conditions
observer[sc.DO("Product 4 Lamp")].addNoChangeCheck(time - TOL)
observer[sc.DO("Product 3 Lamp")].addNoChangeCheck(time - TOL)
observer[sc.DO("Product 2 Lamp")].addNoChangeCheck(time - TOL)
observer[sc.DO("Product 1 Lamp")].addNoChangeCheck(time - TOL)
observer[sc.DO("Dispense Bay Lamp")].addNoChangeCheck(time - TOL)
observer[sc.DO("Change Bay Lamp")].addNoChangeCheck(time - TOL)
observer[sc.DO("Open Cash Box Actor")].addNoChangeCheck(time - TOL)
observer[sc.DO("Cash Box Return Actor")].addNoChangeCheck(time - TOL)
observer[sc.DO("Product 1 Release Gear")].addNoChangeCheck(time - TOL)
observer[sc.DO("Product 2 Release Gear")].addNoChangeCheck(time - TOL)
observer[sc.DO("Product 3 Release Gear")].addNoChangeCheck(time - TOL)
observer[sc.DO("Product 4 Release Gear")].addNoChangeCheck(time - TOL)
observer[sc.CC("GSM Modem")].addNoChangeCheck(time - TOL)
observer[sc.DP("Display")].addNoChangeCheck(time - TOL)

observer.stop()
