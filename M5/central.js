// based on the example on https://www.npmjs.com/package/@abandonware/noble

const noble = require('@abandonware/noble');

const uuid_service = "1101"
const uuid_value = "2101"
const uuid_value2 = "2102"
const uuid_value3 = "2103"

let sensorValue = NaN

noble.on('stateChange', async (state) => {
    if (state === 'poweredOn') {
        console.log("start scanning")
        await noble.startScanningAsync([uuid_service], false);
    }
});

noble.on('discover', async (peripheral) => {
    await noble.stopScanningAsync();
    await peripheral.connectAsync();
    var charUIDs = [uuid_value, uuid_value2, uuid_value3];
    var serUIDs = [uuid_service];
    const {
        characteristics
    } = await peripheral.discoverSomeServicesAndCharacteristicsAsync(serUIDs, charUIDs);
    readData(characteristics)
});

//
// read data periodically
//
let readData = async (characteristic) => {
    const value = (await characteristic[0].readAsync());
    const value2 = (await characteristic[1].readAsync());
    const value3 = (await characteristic[2].readAsync());
    //console.log(value.readFloatLE(0).toFixed(8) + " " + value2.readFloatLE(0).toFixed(8) + " " + value3.readFloatLE(0).toFixed(8));
    sensorValue = value3.readFloatLE(0);
    //console.log(sensorValue);

    // read data again in t milliseconds
    setTimeout(() => {
        readData(characteristic)
    }, 10);
}

//
// hosting a web-based front-end and respond requests with sensor data
// based on example code on https://expressjs.com/
//
const express = require('express')
const app = express()
const port = 3000

app.set('view engine', 'ejs');

app.get('/', (req, res) => {
    res.render('index')
})

app.post('/', (req, res) => {
    res.writeHead(200, {
        'Content-Type': 'application/json'
    });
    res.end(JSON.stringify({
        sensorValue: sensorValue
    }))
    //console.log(sensorValue);
})

app.listen(port, () => {
    console.log(`Example app listening on port ${port}`)
})