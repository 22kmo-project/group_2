const mysql = require('mysql');
const connection = mysql.createPool({
  host: 'localhost',
  user: 'root',
  password: 'test',
  database: 'group_2'
});
module.exports = connection;