const mysql = require('mysql');
const connection = mysql.createPool({
  host: 'localhost',
  user: 'group_2',
  password: 'netpass',
  database: 'group_2'
});
module.exports = connection;