I create a tool named **Super Animation Converter**,
which is a simple **SWF** (a file format supported by **Adobe Flash Player** software) converter.
It can parse and extract transformation data from SWF file. 
With these transformation data and the right images, 
you can reproduce the animation in any game engine just as **Adobe Flash Player** can do.


The native animation solution in Cocos2D game engine is “frame by frame” animation, 
which means if there are 20 frames in your animation, you need 20 pieces of image(texture), 
and draw these images one by one on the screen to create animation effect. There are two flaws in this solution: 

1. High resource consuming, one frame one image;

2. Hard to make smooth animation, since no interpolation between frames, which means it “jumps” directly from the current frame to the next frame.


So I try to provide a better animation solution which is based on Super Animation Converter for Cocos2D game engine. 
The idea is very simple: 

1. Use Flash as your animation editor, create any animation you want in it, then export these animation as SWF file. 

2. Parse the SWF file with Super Animation Converter, get the transformation data and images from the SWF file.

3. Reproduce the animation in Cocos2D game engine with  the transformation data and images.

Please refer to [super_anim_help_english_version.pdf](https://github.com/raymondlu/super-animation-samples/raw/master/super_anim_help_english_version.pdf).


![intro](https://github.com/raymondlu/super-animation-samples/raw/master/intro.png)

New Features
------------------
* Support sprite sheet, which means you can use TexturePacker to pack some small images into one big images
* Support resize animation, you can resize one animation to different size to support multiple resolution
* Support set flip x&y for animation
* Support rename animation sprite name

Contact Me
------------------
   * Forum: [http://www.cocos2d-x.org/boards/6/topics/19621][1]
   * Blog: [http://raymondlu1983.blog.com/super-animation-converter/][2]
   
[1]: http://www.cocos2d-x.org/boards/6/topics/19621 "http://www.cocos2d-x.org/boards/6/topics/19621"
[2]: http://raymondlu1983.blog.com/super-animation-converter/ "http://raymondlu1983.blog.com/super-animation-converter/"