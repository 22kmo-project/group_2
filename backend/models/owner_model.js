const db = require('../database');

const owner = {
  getAllOwnerInfo: function(id, callback) {
    return db.query('select fname, lname, address, phonenumber, email from owner where id_owner = (select id_owner from card where id_card=?)', [id], callback);
  },

  fname: function(fname_owner, callback) {
    return db.query(
      'select fname from owner where id_owner = (select id_owner from card where id_card = ?);',
      [fname_owner.id_card],
      callback
    );
  },
  /*
  getById: function(id, callback) {
    return db.query('select * from owner where id_owner=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from owner', callback);
  },
  add: function(add_owner, callback) {
    return db.query(
      'insert into owner (fname,lname,address,phonenumber,email) values(?,?,?,?,?)',
      [add_owner.fname, add_owner.lname, add_owner.address,add_owner.phonenumber,add_owner.email],
      callback
    );
  },
*/
 /*
  delete: function(id, callback) {
    return db.query('delete from owner where id_owner=?', [id], callback);
  },
  update: function(id, owner, callback) {
    return db.query(
      'update owner set fname=?,lname=?, address=?, phonenumber=?, email=? where id_owner=?',
      [owner.fname, owner.lname, owner.address,owner.phonenumber,owner.email,id],
      callback
    );
  }*/
};
module.exports = owner;