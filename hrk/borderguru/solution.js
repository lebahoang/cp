"use strict";

const pg = require('pg');
const fs = require('fs');
const readline = require('readline');

const user = 'postgres';
const passwd = 'hoangleba';
const host = 'localhost';
const port = 5432;
const database = 'borderguru';


function askQuestion (rl, s, pool) {
  return new Promise(function (resolve) {
    return rl.question('Usage [question_number(1-4) param]\
                      \n1: get order by particular company\
                      \n2: get order by particular address\
                      \n3: delete order by order Id\
                      \n4: display how often each item ordered\
                      \nexit: exit program\
                      \nEx: 1 SuperTrader, 2 Reeperbahn 153, etc\
                      \n\n\nWhat is your question ?\n', function (question) {

      return resolve(question);
    });
  })
  .then(function (question) {
    if (question === 'exit') {
      return question;
    }
    let argvs = question.split(' ');
    let q = argvs[0];
    let param = [];
    for (let i = 1; i < argvs.length; i++) {
      param.push(argvs[i]);
    }
    param = param.join(' ');
    if (q === '1') {
      return s.getOrdersByCompany(pool, param);
    } else if (q === '2') {
      return s.getOrdersByAddress(pool, param);
    } else if (q === '3') {
      return s.deleteOrder(pool, param);
    } else if (q === '4') {
      return s.displayItemsByOften(pool);
    }
    return '';
  })
  .then(function (answer) {
    console.log(answer);
    if (answer === 'exit') {
      return;
    }
    console.log('\n\n\n');
    return askQuestion(rl, s, pool);
  });
}
function solution () {
  this.prepareDb = function (pool) {
    return pool.query('CREATE TABLE if not exists orders ( \
        orderId text, \
        companyName text, \
        address text, \
        orderedItem text, \
        PRIMARY KEY (orderId) \
      );'
    )
    .catch(function (e) {
      console.log('Error' + e);
    });
  };
  this.importData = function (pool) {
    let dataFilePath = 'sample.txt';
    let data = fs.readFileSync(dataFilePath).toString().split('\n');
    let rows = [];
    for (let i = 0; i < data.length; i++) {
      let row = data[i].split(',');
      let orderId = row[0].trim();
      let companyName = row[1].trim();
      let address = row[2].trim();
      let orderedItem = row[3].trim();
      rows.push(`('${orderId}', '${companyName}', '${address}', '${orderedItem}')`);
    }
    // console.log(rows);
    return pool.query('DELETE from orders')
    .then(() =>  pool.query(
      `INSERT INTO orders (orderId, companyName, address, orderedItem)
       VALUES ${rows.join(',')}`)
    )
    .catch(function (e) {
      console.log(e);
    });
  };
  this.getOrdersByCompany = function (pool, companyName) {
    return pool.query(`SELECT * FROM orders WHERE companyName = '${companyName}';`)
    .then(function (answer) {
      return answer.rows;
    })
    .catch(function (e) {
      console.log(e);
    });
  };
  this.getOrdersByAddress = function (pool, address) {
    return pool.query(`SELECT * FROM orders WHERE address = '${address}';`)
    .then(function (answer) {
      return answer.rows;
    })
    .catch(function (e) {
      console.log(e);
    });
  };
  this.deleteOrder = function (pool, orderId) {
    return pool.query(`DELETE FROM orders WHERE orderId = '${orderId}';`)
    .then(function (answer) {
      return 'DELETE ' + answer.rowCount;
    })
    .catch(function (e) {
      console.log(e);
    });
  };
  this.displayItemsByOften = function (pool) {
    return pool.query(`SELECT orderedItem, count(*) as number_of_orders\
                     FROM orders\
                     GROUP BY orderedItem\
                     ORDER BY number_of_orders desc;`)
    .then(function (answer) {
      return answer.rows;
    })
    .catch(function (e) {
      console.log(e);
    });
  }
  return this;
}

let pgConfig = {
  user: user,
  database: database,
  password: passwd,
  host: host,
  port: port,
  max: 10,
  idleTimeoutMillis: 30000,
};
let pool = new pg.Pool(pgConfig);
let s = new solution();
s.prepareDb(pool)
.then(() => s.importData(pool))
.then(function () {
  let rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
  });

  return askQuestion(rl, s, pool)
  .then(function () {
    return pool.end().then(() => rl.close());
  });
});


