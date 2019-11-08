const express   = require('express'),
      fs        = require('fs'),
      app       = express(),
      port      = 3000
var data1, data2

app.use(express.static(__dirname + '/'))
app.use(express.urlencoded({extended: true}))
app.get('/', (req,res) => res.sendFile(__dirname + '/index.html'))
app.route('/data/1')
   .post((req,res) => {
        let fan  = req.body.fan,
            temp = req.body.temp,
            time = new Date(),
            Time = time.toLocaleString()

        data1 = req.body
        res.send(data1)
        
        let data = `Fan: ${fan} || temperature: ${temp} || time: ${Time}`
        fs.appendFile('log1.txt', data+'\n', 'utf8', (err) => {
            if (err) throw err
        })

    })
    .get((req,res) => res.send(data1))

app.route('/data/2')
   .post((req,res) => {
        let fan  = req.body.fan,
            temp = req.body.temp,
            time = new Date(),
            Time = time.toLocaleString()

        data2 = req.body
        res.send(data2)
        
        let data = `Fan: ${fan} || temperature: ${temp} || time: ${Time}`
        fs.appendFile('log2.txt', data+'\n', 'utf8', (err) => {
            if (err) throw err
        })
        
    })
    .get((req,res) => res.send(data2))

app.listen(port, () => console.log("Listening to port " + port))
