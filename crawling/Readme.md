# Simple Crwaler
The first project for Web Search Engin

##Core
The core roles in crwaler.

###Engine

The engine is responsible for controlling the data flow between all components of the system, and triggering events when certain actions occur. See the Data Flow section below for more details.

##Include
The common & base classes work for whole project

###Setting
In charge of reading and writing setting files, the setting files format show as blow:
```
[queue]
length = 500

#some annotation
[thread]
downloader = 10
parser = 5

[Strategies]
black_holds = enable
different_names = enable


...
```

###Log

###Status

###Strategies

###Thread Poll


##Models

##Strategies
