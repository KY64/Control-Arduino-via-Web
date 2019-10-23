const express   = require('express'),
      fs        = require('fs'),
      app       = express(),
      port      = 3000
var log

app.use(express.urlencoded({extended: true}))
app.get('/', (req,res) => res.sendFile(__dirname + '/index.html'))
app.route('/data')
   .post((req,res) => {
        let fan  = req.body.fan,
            temp = req.body.temp,
            time = new Date(),
            Time = time.toLocaleString()

        log = req.body
        res.send(log)
        
        let data = `Fan: ${fan} || temperature: ${temp} || time: ${Time}`
        
        fs.appendFile('log.txt', data+'\n', 'utf8', (err) => {
            if (err) throw err
        })
    })
    .get((req,res) => res.send(log))

app.listen(port, () => console.log("Listening to port " + port))
