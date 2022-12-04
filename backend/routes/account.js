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

router.get('/balance/:id?',
    function (request, response) {
        account.balanceById(request.params.id, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult[0]);
                
            }
        })
    });

    router.get('/credit/:id?',
    function (request, response) {
        account.balanceCreditById(request.params.id, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult[0]);
                
            }
        })
    });

router.post('/balance', 
  function(request, response) {
      account.balance(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult[0]);
      console.log(dbResult);
    }
  });
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

router.post('/getbalance',
function(request,response) {
card.get_balance(request.body, function(err,dbResult){
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
  card.delete(request.params.id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});


router.put('/:id', 
function(request, response) {
  card.update(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;