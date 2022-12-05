const express = require('express');
const { response } = require('../app');
const account = require('../models/account_model');
const router = express.Router();
const card = require('../models/account_model');

router.get('/',
    function (request, response) {
        card.getAll(function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                console.log(dbResult);
                response.json(dbResult);
            }
        })
    });

router.get('/:id?',
    function (request, response) {
        card.getById(request.params.id, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult[0]);
            }
        })
    });


router.post('/', 
function(request, response) {
  card.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(request.body);
      response.json(dbResult.rows);
    }
  });
});

router.post('/savingsmode/:id?',
function(request, response) {
  account.update_savingsmode(request.params.id, function(err, dbResult) {  //testttu myös pelkkä savingsmode
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult[0]);
    }
  });
});

router.post('/getbalance',
function(request,response) {
account.get_balance(request.body, function(err,dbResult){
    if(err) {
        response.json(err);
    } else {
        response.json(request.body);
        response.json(dbResult);
    }
});
});


router.delete('/:id', 
function(request, response) {
  account.delete(request.params.id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});


router.put('/:id', 
function(request, response) {
  account.update(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;
