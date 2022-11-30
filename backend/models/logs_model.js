const db = require('../database');

const logs = {
  getById: function(id, callback) {
    return db.query('call get_logs(?);', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from logs', callback);
  },
  add: function(add_logs, callback) {
    return db.query(
      'insert into logs (id_owner,logsnumber,password,credit) values (?,?,?,?)',
      [add_logs.id_owner, add_logs.logsnumber, add_logs.password,add_logs.credit],
      callback
    ); // tieto lähtee arrayna
  },
  delete: function(id, callback) {
    return db.query('delete from logs where id_logs=?', [id], callback);
  },
  update: function(id, logs, callback) {
    return db.query(
      'update logs set logsnumber=?,password=?, credit=?, id_owner=? where id_logs=?',
      [logs.logsnumber, logs.password, logs.credit,logs.id_owner,id],
      callback
    );
  }
};
module.exports = logs;