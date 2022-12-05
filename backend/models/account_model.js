const db = require('../database');

const account = {
  getById: function(id, callback) {
    return db.query('select * from account where id_account=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from account', callback);
  },
  savingsmode: function(id, callback) { //testi
    return db.query(
      'call update_savingsmode from account where id_card = ?', //kokeiltu myös select ja pelkkä savingsmode
      [id],
      callback
    );
  },
  add: function(add_account, callback) {
    return db.query(
      'call make_card_account(?)',
      [add_account.id_card],
      callback
    ); // tieto lähtee arrayna
  },
  delete: function(id, callback) {
    return db.query('delete from account where id_account=?', [id], callback);
  },
  update: function(id, account, callback) {
    return db.query(
      'update account set accountnumber=?,password=?, credit=?, id_card=? where id_account=?',
      [account.accountnumber, account.password, account.credit,account.id_card,id],
      callback
    );

  },
};
module.exports = account;