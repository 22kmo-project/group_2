const db = require('../database');

const account = {
  getById: function(id, callback) {
    return db.query('call get_balance(?)', [id], callback);
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

  balanceById: function(id, callback) {
    return db.query(
      'select account_balance from account where id_card = ?',
      [id],
      callback);
     // tieto lähtee arrayna
  },

  balanceCreditById: function(id, callback) {
    return db.query(
      'select credit_balance from account where id_card = ?',
      [id],
      callback);
     // tieto lähtee arrayna
  },

  delete: function(id, callback) {
    return db.query('delete from account where id_account=?', [id], callback);
  },
  update: function(id, account, callback) {
    return db.query(
      'update account set account_balance=? where id_account=?',
      [account.account_balance, id],
      callback
    );
  },
};



module.exports = account;