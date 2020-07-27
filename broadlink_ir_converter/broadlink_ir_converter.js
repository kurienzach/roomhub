const { broadlinkToPulesArray, pulesArrayToBroadlink } = require('broadlink-ir-converter');

// const broadlinkCommand = '2600600000012994131313121312141213121313131213121436133713131312133614361436143614361436141213361412131313121336141213131336141213361436143614121300056900012A4914000C5E0001294A14000C5D00012A4A13000D050000000000000000';
const broadlinkCommand = '26007800000129921313131312131213121313131213121312381238121312131238123812371337121313131213123810151213121312381139103a123711151039133711391015120005740001274b10000c6c0001274b11000c6b0001264b12000c6a0001264c10000c6c0001264b11000c6a0001264c10000d05';

const convertedPulesArray = broadlinkToPulesArray(broadlinkCommand);

newArray = convertedPulesArray.slice(1)
// newArray = convertedPulesArray
console.log(newArray);
hexArray = newArray.map(i => (i & 0xFFFF).toString(16));
// console.log(hexArray)
hexArray.map(i => {
    if (i.length > 2) {
        return `${i.slice(-2)} ${i.slice(0, i.length - 2)}`
    }
    return i;
}).forEach(i => process.stdout.write(i + " "));
console.log(convertedPulesArray.length - 1);

