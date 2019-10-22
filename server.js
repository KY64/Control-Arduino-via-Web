const express   = require('express'),
      fs        = require('fs'),
      app       = express(),
      port      = 3000

app.use(express.urlencoded({extended: true}))
app.get('/', (req,res) => res.sendFile(__dirname + '/index.html'))
app.post('/data', (req,res) => {
    let fan  = req.body.fan,
        temp = req.body.temp,
        time = new Date(),
        Time = time.toLocaleString()

    res.send(req.body)
    
    let data = `Fan: ${fan} || temperature: ${temp} || time: ${Time}`
    
    fs.appendFile('log.txt', data+'\n', 'utf8', (err) => {
        if (err) throw err
    })
})

app.listen(port, () => console.log("Listening to port " + port))
