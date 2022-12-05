const express = require('express');
const logs = require('../models/logs_model');
const router = express.Router();


router.get('/',
    function (request, response) {
        logs.getAll(function (err, dbResult) {
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
        logs.getById(request.params.id, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult[0]);
            }
        })
    });

    router.get('/latest/:id?',
    function (request, response){
      logs.getlatestlog(request.params.id,function(err, dbResult){
        if (err){
          response.json(err);
        }
        else {
          response.json(dbResult[0]);
        }
      })
    });



    router.get('/latestsave/:id?',
    function (request, response){
      logs.getlatestsave(request.params.id,function(err, dbResult){
        if (err){
          response.json(err);
        }
        else {
          response.json(dbResult[0]);
        }
      })
    });

router.post('/', 
function(request, response) {
  logs.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(request.body);
      response.json(dbResult.rows);
    }
  });
});


router.delete('/:id', 
function(request, response) {
  logs.delete(request.params.id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});


router.put('/:id', 
function(request, response) {
  logs.update(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;
