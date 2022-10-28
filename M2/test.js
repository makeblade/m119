// based on the example on https://www.npmjs.com/package/@abandonware/noble

const noble = require('@abandonware/noble');

const uuid_service = "1101"
const uuid_value = "2101"
const uuid_value2 = "2102"
const uuid_value3 = "2103"

noble.on('stateChange', async (state) => {
  if (state === 'poweredOn') {
    console.log("start scanning")
    await noble.startScanningAsync([uuid_service], false);
  }
});

noble.on('discover', async (peripheral) => {
  try {
    await noble.stopScanningAsync();
    await peripheral.connectAsync();
    var charUIDs = [uuid_value, uuid_value2, uuid_value3];
    var serUIDs = [uuid_service];
    const {characteristics} = await peripheral.discoverSomeServicesAndCharacteristicsAsync(serUIDs, charUIDs);
    readData(characteristics);
  } catch(error) {
    console.log(error);
  }
});

//
// read data periodically
//
let readData = async (characteristic) => {
  const value = (await characteristic[0].readAsync());
  const value2 = (await characteristic[1].readAsync());
  const value3 = (await characteristic[2].readAsync());
  console.log(value.readFloatLE(0) + " " + value2.readFloatLE(0) + " " + value3.readFloatLE(0));

  // read data again in t milliseconds
  setTimeout(() => {
    readData(characteristic)
  }, 10);
  
}