**View our hackster article [here](https://www.hackster.io/dect/b-hive-a14efa "Hackster Article").** 

# B-Hive
B-hive is an autonomous electronic monitoring device enabling beekeepers to oversee their hives' well-being.

[insert photo]

__Bees have been facing the threat of extinction for more than fifteen years. Indeed, from 30 to 40 % of bee colonies died within the last decade in Europe. This is an alarming situation for the environment since bees are the most important pollinators and therefore, an integral part of our ecosystem. Moreover, an economic issue arises. Indeed, for example in France, honey production is the additional income for more than 54,000 beekeepers and the main one for about 2,000 others.__

__Our goal is to enable beekeepers, professional or amateur, to monitor their hive remotely. Our solution is designed to save them unnecessary trips to their production site, and therefore save time. Our device is a connected sensor kit that collects data every 10 minutes and sends them to the beekeeper. This informs him on the state of his bee colonies and the quality of their environment. Our product is easy to use and affordable (about 150 €) compared to other commercialized systems.__


## Data studied
To monitor the hive's integrity we chose to study :

* Indoor temperature (+/- 0.5 °C)
* Outdoor  temperature (+/- 0.5 °C)
* Outdoor Humidity (+/- 2%)
* Weight (+/- 0.2 kg)


We also spent a large amount of time working on an Artificial Intelligence (AI) which would have been able to indicate whether or not there was a queen bee and if there were any bees at all.  Unfortunately, we were not able to implement our neural network (NN) since exporting it proved to be more intricate than expected.

## Software 
_The Mbed source file is available to download in the Code tab._

For our system to work, we developed the software on Mbed. With the code we can :

* __Initialize all the sensors.__
For each sensors, we assigned a pin.

* __Get value measurements for each sensors every ten minutes.__
> Indoor temperature : We chose to use the DS18B20 temperature sensor. Indeed, this model already proved its efficiency in previous similar projects.

> Outdoor temperature and humidity  : We chose the DHT22 temperature and humidity sensor.

> Weight : We choose to use a strain gauge to collect weight values.

* __Send data that we have collected to Sigfox Backend.__

* __Put the micro-controller in sleep when we aren't sending data.__

## AI Training

To create our Artificial Intelligence, we decided to train a neural network to analyze sound frequency in a hive. To that end, we used Edge Impulse which is a development platform. It allows you to conceive a device with embedded machine learning effortlessly.

After creating an Edge Impulse account and a project, we had the choice between two methods to train our neural network.

The first one required the use of and IoT discovery kit which we connected to Edge Impulse following this tutorial. Then, to develop an IA able to recognize different sound frequencies, we followed the steps as explained here.

The second methods did not required the B-L475E-IOT01A2 board. However, it was extremely time consuming. Indeed, after searching and downloading data sets (to bee or not to bee and The Hiveeyes Community), each sound sample had to be hand cut and uploaded in our design. For the majority of our project, we chose this method since we were unable to collect samplings directly from a hive.

To begin, we created an impulse design and set the parameters required to train our AI. Because we are dealing with bees, we needed to take a bigger window size than the one demonstrated in the tutorial. We chose to use an MFCC bloc to train our neural network, but it was not our only option. The MFE and Spectogram blocks could have also served to train the AI. Depending on the range of frequency studied, either bloc could have worked better than the others.

## PCB Making

## Sigfox and Ubidots

## System Energy Source 

## System Assembling
