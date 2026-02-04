using RPGMenuSystem.MenuSystem;

namespace RPGMenuSystem.UI;

public class TitleScreen
{
    private MenuManager _menuManager;
    private Action<TitleScreenChoice> _onChoice;

    public TitleScreen(Action<TitleScreenChoice> onChoice)
    {
        _menuManager = new MenuManager();
        _onChoice = onChoice;
    }

    public void Show()
    {
        var titleMenu = new Menu
        {
            Title = GetTitleArt(),
            Items = new List<MenuItem>
            {
                new MenuItem { Text = "New Game", OnSelect = () => _onChoice(TitleScreenChoice.NewGame) },
                new MenuItem { Text = "Continue", OnSelect = () => _onChoice(TitleScreenChoice.Continue) },
                new MenuItem { Text = "Load Game", OnSelect = () => _onChoice(TitleScreenChoice.LoadGame) },
                new MenuItem { Text = "Settings", OnSelect = () => _onChoice(TitleScreenChoice.Settings) },
                new MenuItem { Text = "Credits", OnSelect = () => _onChoice(TitleScreenChoice.Credits) },
                new MenuItem { Text = "Exit", OnSelect = () => _onChoice(TitleScreenChoice.Exit) }
            }
        };

        _menuManager.OpenMenu(titleMenu);

        while (_menuManager.CurrentMenu != null)
        {
            RenderTitleScreen();
            var key = Console.ReadKey(true).Key;
            _menuManager.HandleInput(key);
        }
    }

    private void RenderTitleScreen()
    {
        Console.Clear();
        Console.ForegroundColor = ConsoleColor.Cyan;
        
        string[] titleArt = new[]
        {
            @"",
            @"    ╔═══════════════════════════════════════════════════════════════════╗",
            @"    ║                                                                   ║",
			@"    ║            Eternal Kingdoms Online
    
                                 Age of Sovereigns  
                                                                                      ║",
            @"    ║            An Epic RPG Adventure Awaits...                        ║",
            @"    ║                                                                   ║",
            @"    ╚═══════════════════════════════════════════════════════════════════╝",
            @""
        };

        foreach (var line in titleArt)
        {
            Console.WriteLine(line);
        }

        Console.ResetColor();
        Console.ForegroundColor = ConsoleColor.Yellow;
        Console.WriteLine("\n                              === MAIN MENU ===\n");
        Console.ResetColor();

        if (_menuManager.CurrentMenu != null)
        {
            for (int i = 0; i < _menuManager.CurrentMenu.Items.Count; i++)
            {
                var item = _menuManager.CurrentMenu.Items[i];
                var prefix = i == _menuManager.CurrentMenu.SelectedIndex ? "    >>> " : "        ";
                var color = item.IsEnabled ? ConsoleColor.White : ConsoleColor.DarkGray;

                Console.ForegroundColor = color;
                Console.WriteLine($"{prefix}{item.Text}");
                Console.ResetColor();
            }
        }

        Console.ForegroundColor = ConsoleColor.DarkGray;
        Console.WriteLine("\n\n    [Arrow Keys: Navigate | Enter: Select | Esc: Back]");
        Console.ResetColor();
    }

    private string GetTitleArt()
    {
        return "THE LEGEND OF THE 72 REALMS";
    }
}

public enum TitleScreenChoice
{
    NewGame,
    Continue,
    LoadGame,
    Settings,
    Credits,
    Exit,
    None
}
