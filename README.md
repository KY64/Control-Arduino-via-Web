#  Control ESP8266 via Web
I use Wemos D1 to connect a website so I could control the device and read its data from website. I use **ExpressJS** to create the server so you need to install [NPM](https://nodejs.org/en/) first if you want to make it work.

### Requirements
*	Wemos D1
*	Arduino IDE
*	[NPM (Node Package Manager)](https://nodejs.org/en/)

###  Cloning repository

```https://github.com/KY64/Control-ESP8266-via-web.git```

or **[Download the zip file](https://github.com/KY64/Control-ESP8266-via-web/archive/master.zip)**

###  Getting started
1.	Install the package by running `npm i`
2.	Run the server using `npm run test`

## UPDATE
**24/10/2019**

I added ethernet support so it could send data to the web via ethernet. You need to set your IP as static and also don't forget to set it also in the arduino code.
