# UnoDiam Demo Alpha
[![License](https://img.shields.io/badge/LICENSE-UnoDiam%20DA-green?style=for-the-badge)](/LICENSE.md)

UnoDiam Demo Alpha is a project to demonstrate the structure and functionality of the UnoDiam project. There is every reason to consider this repository "technical" because it is intended for demonstration only to some people.
###### Note that the following file will use "Platform" instead of "UnoDiam".

## The Goal
The main task of the Platform is to organize the rapid operation of the system without the need for developers (or rather, assemblers) to write high-performance code.
Due to the fact that there will be many ready-made parts of different functionality in the platform, the assembler will be able to create a system with the desired functionality by configuring the system. This will allow you to create a fast system (because there are fewer places where you can write bad code) without having to write high-performance code.
Instead of writing productive code, the platform requires the assembler to have a clear understanding of how system (something created on base of UnoDiam) should work and what is need to do for what, otherwise nothing will come.
The platform allows you to combine any functionality into the desired system. You will be able to take advantage of, for example, all bot frameworks in one. It is important to note that initially the platform was created in order to be able to combine different things into something universal.

The fundamental difference from writing a program with your hands using libraries is that the main responsibility for performance is borne by the modules and the core. The modules themselves must be designed to provide maximum interoperability performance. The assembler is given the opportunity to link these modules in different ways, which will change the functionality of the system. However, in any connection configuration, the modules and the core are responsible for performance. That is, the performance of the connections will depend only on the selected modules and the core version. However, just building links is not enough to lay down functionality. Each module can give quite a lot of settings to refine its work. The assembler may need to fill in a configuration file or write a script. In the case of a configuration file, the assembler will not be able to affect performance with incorrect settings (if the settings are incorrect, there is an extremely high chance that the system will not work). In the case of scripts, the assembler will be given a fairly narrow scope of implementation, such as the placement of conditions - the assembler will have very little opportunity to optimize the script, and to write bad code. And do not forget that bad code in the script can probably lead to a different result of the system (in terms of functionality), so it is unlikely that the bad code will not have to fix the assembler itself.

### The tasks of the "system":
The system created on the platform will have 2 main characteristics:
1.  stable work of the system at any time after full startup;
2.	work in constant conditions of Operating System.

The first point means that after a full start of the system, provided there are no problems on the side of the operating system and neighboring programs that affect the operation of the platform, the platform will be able to work equally in 5 minutes and 20 years. Simply put, this item means no errors that can interrupt the normal operation of the platform from the platform at a time when it has already successfully launched. The platform itself will not break :)

The second paragraph makes a clarification in the first paragraph. Namely: the platform will work ONLY if there are no changes to it. For example, you do not run a render that eats up all the RAM and performance of the computer after the successful launch of the platform, do not disable the disk on which the platform runs after its successful launch, etc.only data can Change in the system. After the platform is launched, its configuration and workspace configuration should remain unchanged.
