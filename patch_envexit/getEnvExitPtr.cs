using System;
using System.Collections.Generic;
using System.Reflection;

namespace EnvExit
{
	class Program
	{
		static void Main(string[] args)
		{
			var methodList = new List<MethodInfo>(typeof(Environment).GetMethods(BindingFlags.Static | BindingFlags.Public | BindingFlags.NonPublic)); //extracts all methods as per binding flag
			Console.WriteLine(((methodList.Find((MethodInfo mi) => mi.Name == "Exit")).MethodHandle.GetFunctionPointer()).ToString("X")); //  prints function pointer for method in hex format
		}
	}
}
