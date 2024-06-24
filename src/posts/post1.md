
# AC2 Game Reversing

## Introduction
In this project, I reverse engineered Assassins Creed 2 to get unlimited currency and health using Reclass, IDA, and Cheatengine. I made this to be a general educational guideline for how these tools can be used to reverse engineering games.
 
I do not recommend anyone to implement these techniques and this is strictly for educational purposes.
## Technologies/Tools Used
Reclass

Cheatengine

IDA Pro 

x32dbg

## Initial Setup
Before diving into the specifics of reverse engineering in games, it's important to understand that usually games will be packed. So first you might have to understand and unpack the game's protection mechanism. Using x32dbg can be a good tool for analyzing how these are used.

It's crucial to remember that bypassing protective measures is illegal and some games include terms of service specifying that. Therefore, I will not provide any instructions on how to bypass these protections. This project will focus on the legal and ethical aspects of reverse engineering the games mechanics.

## Currency
For games and in general, cheatengine can be a very underrated tool for reverse engineering. To use cheatengine effectively, you need to identify a few things first.
Is the value a/n:
- integer
- float
- double
- string

Your value could be a different data type, but generally for games these will almost always be the data types you will be looking for. In my case I am looking for an integer of a known value. So I will scan for the value ex: 100.

Then I will spend/gain money and scan again for the value being changed by x amount. Depending on how big the game is, and if your value is known, you should find the value you are looking for. 

After getting to the result, you can find what accesses that address by right clicking which internally places a hardware breakpoint on that address.

![unnamedpost1](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/unnamedpost1.png
)

For currency I looked at the instructions being used at each address and used some common sense of what would be used to change the currency. Here we can see at the bottom, it is comparing esi to edi + 34, then a condition checking if the value is still equal to another, otherwise it moves a value to another location.

```
Instructions:
- cmp: Compares the contents of general-purpose register (GPR) RA with the contents of GPR RB as signed integers and sets one of the bits in Condition Register Field BF

- mov: Copies the data item referred to by it's second operand ```

I thought that seemed logical for a way to check for the value of currency being changed so I checked the address where this was being implemented in IDA

![image-68](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-68.png
)

Following the flow of the program we eventualy get here:

![image-69](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-69.png
)

Where it pushes an offset labeled `aSetPlayerFunds`

Stepping in .rdata we can see the value tied to our player funds:

![image-70](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-70.png
)
## Player Health

For player health it is a bit different. In my case, the health we are trying to find the value of is an unknown initial value. So we scan for an unknown initial value in cheatengine. There will likely be multiple results, for each address, I found the base address of the class and opened it in Reclass.

![image-71](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-71.png
)
Here is the base address circled in blue. As seen from the last photo the base address is moved from `esi+58` into `ecx` then being compared

![image-72](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-72.png
)

 Then I discovered that at index 4 (5th entry) of every VTable, which is the first pointer in the class, there is a pointer to the NAME of the class.

 In reclass:

![image-73](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-73.png
)

Following that VTable address in IDA,

![image-74](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-74.png
)

Then stepping in the offset:

![image-75](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-75.png
)



![image-76](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-76.png
)

And here in .data we can find the value tied to our players health called `aCsrvplayerhealth`.

Now all that's left is to create a DLL that modifies the game's memory at the addresses, then use an injector tool or write your own.


## Results
Health: Here the health bar is in the top left, in this clip you can see my character jumping off a building and getting absolutely destroyed while receiving no damage (increased playback speed because they take forever to attack)

https://drive.google.com/file/d/10U6RN4tlk2JXzOXwdK20ItP_pnWIdd2V/view?resourcekey


Currency: In this clip you can see my character pickpocketing an NPC and receiving a very large number of funds. (normally for pickpocketing you receive ~20f)

https://www.youtube.com/watch?v=37kk4Kf21S0


## Conclusion

In today's online games, there will be additional things we have to consider with anti-cheat engines being tied to games. However not all games have anti-cheat's and some do not always work. But tread with caution as cheating in video games can be illegal in certain circumstances. Also there is a chance of being banned from playing the game. I do not recommend anyone to implement these techniques and this is strictly for educational purposes.
