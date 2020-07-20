const { broadlinkToPulesArray, pulesArrayToBroadlink } = require('broadlink-ir-converter');
 
const broadlinkCommand = '2600600000012994131313121312141213121313131213121436133713131312133614361436143614361436141213361412131313121336141213131336141213361436143614121300056900012A4914000C5E0001294A14000C5D00012A4A13000D050000000000000000';

 
const convertedPulesArray = broadlinkToPulesArray(broadlinkCommand);


console.log(JSON.stringify(convertedPulesArray.slice(1)));
console.log(convertedPulesArray.length - 1);
 
