using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {
            string fileName = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments), "MiniDumpDemo_Mainline.mdmp");

            using (FileStream fs = new FileStream(fileName, FileMode.Create, FileAccess.ReadWrite, FileShare.Write))
            {
                try
                {
                    File.Open("1.txt", FileMode.Open);
                }
                catch (Exception e)
                {
                    MiniDump.Write(fs.SafeFileHandle, MiniDump.Option.WithFullMemory);
                }
            }

        }
    }
}
