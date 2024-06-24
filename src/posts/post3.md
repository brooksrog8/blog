# Opera Data Collection Analysis Part 1: Broswer_assistant




In this series I will be doing an analysis of the Opera browser. You may have heard of opera as it has been promoted by some of the most popular creators on youtube and other streaming platforms. There has been some buzz around it of people saying that the Opera GX platform was "spyware" by tracking your location, and stealing users' data. In this analysis I will first be searching through the modules the Opera browser uses and seeing exactly if/how they get a user's location, and uncovering other invasive tasks they perform. I will be initially focusing on if they get a user's exact location and then later uncovering what data they collect.


## Motivation


The reason I decided to start this journey of reversing the Opera browser was due to this program being bundled with other software and ended up on my device without my consent. I found this was both annoying and a bit sketchy, driving me to look into it further. After a bit of research, I saw people accusing it of being "spyware" and decided that I would investigate it myself and see.


In this series I will go over the modules:

- opera.exe

- opera_browser.dll

- opera_elf.dll

- browser_assistant.exe


In this initial entry, I will be going over browser_assistant.exe


## Getting Geo Location


As previously said, I heard some buzz that this application tracks your exact location. So with that being said I thought a good first step would be to run wireshark and open the browser to see if it makes any sketchy requests to speed up the reversing process.


![image-58fixPost3](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-58fixPost3.png
)

This is what we see just from opening the browser


We see some suspicious requests like autoupdate.geo.opera.com, us-autoupdate.opera.com, weather-2.geo.opera.com, and others.


![image-59](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-59.png
)


Clearly by looking at our browser it is getting my location somehow, but is the browser_assistant module the culprit?




First thing I normally do after opening a program in IDA is go to imports and exports, then I decided to search for strings related to geolocation since that is what I was seeing users raving about. Off the bat we see a few,
in the imports tab we will see this:


![image-60](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-60.png
)


And for the strings:


![image-61](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-61.png
)


Let's follow `GetGeoInfoW` first.


![image-60post3](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-60post3.png
)


![image-61post3](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-61post3.png
)
As we can see here `getGeoInfoW` is a Windows API function to get location information.


![image-62post3](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-62post3.png
)


GetUserGeoID is used here and passed with 0x10u (unsigned 16 in hexadecimal)


Looking at the parameters for GetUserGeoID in windows documentation we can see that it is wanting the geographical nation.


![image-63post3](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-63post3.png
)




Now looking back at UserGeoID, so we can find our UserGeoID value in C:


![image-64post3](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-64post3.png
)


As you can see we get the value 244, and looking at the documentation for UserGeoID and going to the table of Geographical locations:


![image-1post3](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-1Post3.png
)
![image-2post3](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-2Post3.png
)




We can see that it will be able to find the user's current country, however that's a very large scope of people so not that invasive. Let's see if it uses that information to narrow the search down.
In the if statement, it checks if the geo information is == 3 (checking if the retrieved ISO 2-letter country code is returned), and if it does another conditional check for if the returned iso 2-letter country code is valid (not returning XX in ASCII)


It then checks if the geographic data corresponds to YU (Yugoslavia, though this country no longer exists) or CS (Serbia and Montenegro, which also no longer exists).
If either of these conditions is met, it sets the geographic data to RS, which corresponds to Serbia (ISO 3166-1 alpha-2 code for Serbia is RS).


It then proceeds to check for various other nations and does some handling for them


Following the cross references, this is the main function where the geolocation checking starts taking place named `geoProcessAndNotify`


![replace33post3](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/replace33post3.png
)

There are some other functions inside `geoProcessAndNotify` that do interesting things like checking what times you open up the browser, if you're in incognito mode, what language to have for your preferences, country overrides, however none of the content seems to be too abnormal for a browser.


I had some difficulties wanting to investigate too many functions because they looked interesting, but we have to remember that this is a browser and a lot of what it's checking is completely necessary. With that being said, a lot of the code being used we do not care about at all.


So inside this main `geoProcessAndNotify` function from the last photo, we see a function inside of it I named `geoFromSetup` on line 89


![image-64post3pt2](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-64post3pt2.png
)




Stepping inside `geoFromSetup` we see:


![image-35](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-35.png
)


Here it just sets up a basic array structure getting ready to hold some data then calls `geoAfterbase`


![image-36](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-36.png
)




Here `geoAfterBase` initializes v4 to -1 and then passes its address to `geobaseCall`


![image-37fixpost3](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-37fixpost3.png
)
![alt text](image.png)

And then here we are back at the first reference from .rdata


So we can see by backtracking the cross references it does for sure have our location, and it's storing it in a structure to hold it.


![image-62post3pt2](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-62post3pt2.png
)


So after it returns from the function that retrieves our geo region, it then takes the value and copies it to a string in the subroutine `callingStrCopies` which returns the value along with other data to `&v36`.


![image-44post3](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-44post3.png
)


Some strings are copied at locations in memory after `a1` then returns `a1` which serves as a buffer.


![image-45post3](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-45post3.png
)




![image-46post3](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-46post3.png
)


`v36` is then moved into `v14`, and `v45` then called in a function i've named timeStamping passing the value of the data `v45` as an argument, so now our geo data is in `v45` when this is called:


![image-53post3](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-53post3.png
)


Stepping inside this is what we see:


![image-54post3](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-54post3.png
)


There are two functions that we will be looking at in here:


- operaLastSeen

- creationAndRunTimeStamp


First inside `operaLastSeen`


Here we can see some interesting functions and some strings telling us what is going on. We see that it is timestamping every first run of the browser. Stepping inside the `operaLastseen` function at the top:


![image-55post3](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-55post3.png
)


We can see here that it includes some more strings telling us that it also tracks the last run of the browser.




Then into `creationAndRunTimestamp` which takes a parameter that assigns `v34` to `a3` that gets passed.
![image-50post3](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-50post3.png
)


![image-51post3](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-51post3.png
)
And thankfully there's some strings to help us see that this function is used for timestamp management and some profile creation operations.






So it gets our country using the windows api, our time using GetSystemTimeAsFileTime, and our last use which stamps our runtime, but never sends it across any network for them to keep. So it does have our approximate location down to our timezone, but so far in this module, does not get our exact location.


## Getting IP address


![image-38post3](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-38post3.png
)


Another method they possibly could have used was getting a users ip using the `getaddrinfo` Windows API and then querying an IP location service, but it was clear they needed to use it for resolving domain names and other common browser functions.


Also we saw from running the program in Wireshark that it made no requests to an IP service to get our location. This is interesting because that was the strategy of the OperaGX browser, this means either:
- The broswer_assistant module is not involved with getting users location


- Opera has made an update to no longer get the users exact location via IP services and uses a new method


We know for a fact that it DOES get the users location seen from the screenshots at the start, so Opera not getting the users location isn't a possibility.






## /autoupdate.geo.opera
Now as shown previously in wireshark, it makes a request to a domain that seems rather suspicious and we can find it in the browser_assistant module.




![image-40](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-40.png
)


However by looking at the cross references, this function clearly does nothing. I suspect this is likely used from another module in the program folder, so we will be revisiting this in the future.




![image-41](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-41.png
)




# Conclusion
In conclusion, it seems clear that the `browser_assistant` module does not operate as spyware according to our goal of finding where our coordinates are being tracked. Instead it performs normal IP address retrieving, and identifying general geo locations on the country level, and gathering statistics related to browser usage or connectivity. There is some statistical collection of what sites you visit, however I consider that rather normal in my opinion since the data collected is anonymized in this instance.


The functions we reviewed are common functionalities in network libraries and tools used by applications for ensuring network connection and basic network-related info.


While the `browser_assistant` module may perform some data gathering and statistical operations, its level of invasiveness appears minimal and does not seem to involve tracking users exact coordinates or engaging in spyware-like behavior. However analysis of additional functionalities in other modules might reveal more information or potential concerns, should that be the case we will be revisiting this.











The reason I decided to start this journey of reversing the Opera browser was due to this program being bundled with other software and ended up on my device without my consent. I found this was both annoying and a bit sketchy, driving me to look into it further. After a bit of research, I saw people accusing it of being "spyware" and decided that I would investigate it myself and see.