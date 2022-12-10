const db = require('../database');

const account = {
  getById: function(id, callback) {
    return db.query('select account_balance from account where id_card = ?', [id], callback);
  },
  getsavingsmode: function(id,callback) { // FRONTIN SAVINGS TARKASTUSTA VARTEN
    return db.query(
      'select savingsmode from account where id_card = ?',
      [id], callback
    );  
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
  update_savingsmode: function( update, callback) { //testi
    return db.query(
      'call update_savingsmode(?,?)' , 
      [update.id_card, update.savings],
      callback
    );
  },/*
  getAll: function(callback) {
    return db.query('select * from account', callback);
  },
  add: function(add_account, callback) {
    return db.query(
      'call make_card_account(?)',
      [add_account.id_card],
      callback
    ); // tieto lähtee arrayna
  },*/

 
/*
  delete: function(id, callback) {
    return db.query('delete from account where id_account=?', [id], callback);
  },
  update: function(id, account, callback) {
    return db.query(
      'update account set accountnumber=?,password=?, credit=?, id_card=? where id_account=?',
      [account.accountnumber, account.password, account.credit,account.id_card,id],
      callback
    );
  },*/
};
module.exports = account;