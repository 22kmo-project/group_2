const db = require('../database');

const account = {
  getById: function(id, callback) {
    return db.query('select * from account where id_account=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from account', callback);
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
  savingsmode: function(savings_account, callback) { //testi
    return db.query(
      'select savingsmode from owner where id_owner = (select id_account from account where id_card = ?);',
      [savings_account.id_card],
      callback
    );
  },
};
module.exports = account;