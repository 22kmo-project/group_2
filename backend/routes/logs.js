const express = require('express');
const router = express.Router();
const logs = require('../models/logs_model');

router.get('/',
    function (request, response) {
        logs.get(function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                console.log(dbResult[0]);
                response.json(dbResult[0]);
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

router.post('/', 
function(request, response) {
  logs.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(request.body);
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
