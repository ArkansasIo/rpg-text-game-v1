namespace RPGMenuSystem.UI;

public class LoadingScreen
{
    public static void Show(string message = "Loading...")
    {
        Console.Clear();
        Console.ForegroundColor = ConsoleColor.Cyan;
        
        Console.WriteLine("\n\n\n\n\n");
        Console.WriteLine($"                              {message}");
        Console.WriteLine();
        
        ShowProgressBar();
        
        Console.ResetColor();
    }

    public static void ShowWithProgress(string message, Action loadingAction)
    {
        Console.Clear();
        Console.CursorVisible = false;

        Console.ForegroundColor = ConsoleColor.Cyan;
        Console.WriteLine("\n\n\n\n");
        Console.WriteLine($"                              {message}");
        Console.ResetColor();

        // Show animated loading bar
        var loadingThread = new Thread(() =>
        {
            string[] frames = new[] { "?", "?", "?", "?", "?", "?", "?", "?", "?", "?" };
            int frameIndex = 0;

            while (true)
            {
                Console.SetCursorPosition(40, 6);
                Console.ForegroundColor = ConsoleColor.Green;
                Console.Write($"{frames[frameIndex]} Loading...");
                Console.ResetColor();

                frameIndex = (frameIndex + 1) % frames.Length;
                Thread.Sleep(100);
            }
        });

        loadingThread.IsBackground = true;
        loadingThread.Start();

        // Execute the loading action
        loadingAction();

        // Stop animation
        loadingThread.Interrupt();
        Console.CursorVisible = true;
    }

    public static void ShowZoneTransition(string fromZone, string toZone)
    {
        Console.Clear();
        Console.ForegroundColor = ConsoleColor.Yellow;
        
        Console.WriteLine("\n\n\n\n\n");
        Console.WriteLine("                              ??????????????????????????????");
        Console.WriteLine($"                              ?  Leaving: {fromZone.PadRight(15)} ?");
        Console.WriteLine("                              ?            ?               ?");
        Console.WriteLine($"                              ?  Entering: {toZone.PadRight(14)} ?");
        Console.WriteLine("                              ??????????????????????????????");
        
        Console.ResetColor();
        
        ShowProgressBar(20);
    }

    private static void ShowProgressBar(int delay = 30)
    {
        Console.WriteLine();
        Console.SetCursorPosition(30, Console.CursorTop);
        Console.Write("                    [");

        Console.ForegroundColor = ConsoleColor.Green;
        for (int i = 0; i < 50; i++)
        {
            Console.Write("?");
            Thread.Sleep(delay);
        }
        Console.ResetColor();
        
        Console.Write("]");
        Thread.Sleep(200);
    }

    public static void ShowSavingScreen()
    {
        Console.Clear();
        Console.ForegroundColor = ConsoleColor.Yellow;
        
        Console.WriteLine("\n\n\n\n\n");
        Console.WriteLine("                              ??????????????????????????????");
        Console.WriteLine("                              ?       Saving Game...       ?");
        Console.WriteLine("                              ?   Please do not turn off   ?");
        Console.WriteLine("                              ?       your system          ?");
        Console.WriteLine("                              ??????????????????????????????");
        
        Console.ResetColor();
        ShowProgressBar(20);
        
        Console.ForegroundColor = ConsoleColor.Green;
        Console.WriteLine("\n\n                              Save Complete!");
        Console.ResetColor();
        Thread.Sleep(1000);
    }
}
