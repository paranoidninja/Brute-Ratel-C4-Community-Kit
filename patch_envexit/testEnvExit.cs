using System;
using System.Collections.Generic;
using System.Reflection;

namespace EnvExit
{
	class Program
	{
		static void Main(string[] args)
		{
			Console.WriteLine("Before Exit");
            Environment.Exit(0);
            Console.WriteLine("Process Did not Exit. Patch Success\n");
		}
	}
}
