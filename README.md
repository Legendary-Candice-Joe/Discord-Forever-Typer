# Discord Forver Typing Message.

A very simple program just written in one C file.
I'm not the best at C but oh well.

The source is **technically** designed for Windows but 
all it needs is libcurl to compile. So this could be easily ported to other systems.

# WARNING

This appearently is against Discord's terms of service, as such this
could lead to account termination. This program sends a User-Agent along
with it's request which lowers the chances but there is always a risk.

# Is this safe?

Well it is open source and the code is only 90 lines long but
no one is forcing you to use this. This is just a quick little script
that I whipped up.

It just sends a https request to discord with the channel ID and token.
If you take a look yourself, there is no logging. It simply just sends this
straight to discord.

But hey I don't blame anyone if they don't trust some random person, it's up to you.

# How to use?

The program tells you but still.
Run the compiled exe (typer) as
Typer.exe ChannelID DiscordToken

It's super easy and it just resends the same request every 9 seconds.

## No error reporting!

As I said, wrote this when I was tired, and quickly.
No error reporting it will simply say error.

# How to compile.

I think this needs no explaination but I'll do it anyway.

First you need MinGW and the libcurl binaries.
Run GCC -L/path/to/lib/ -I/path/to/include discord.c -lcurl -o bin/typer.exe
