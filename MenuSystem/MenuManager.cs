namespace RPGMenuSystem.MenuSystem;

public class MenuManager
{
    private Stack<Menu> _menuStack = new();
    public Menu? CurrentMenu => _menuStack.Count > 0 ? _menuStack.Peek() : null;

    public void OpenMenu(Menu menu)
    {
        _menuStack.Push(menu);
    }

    public void CloseCurrentMenu()
    {
        if (_menuStack.Count > 0)
            _menuStack.Pop();
    }

    public void CloseAllMenus()
    {
        _menuStack.Clear();
    }

    public void HandleInput(ConsoleKey key)
    {
        if (CurrentMenu == null) return;

        switch (key)
        {
            case ConsoleKey.UpArrow:
            case ConsoleKey.W:
                CurrentMenu.NavigateUp();
                break;
            case ConsoleKey.DownArrow:
            case ConsoleKey.S:
                CurrentMenu.NavigateDown();
                break;
            case ConsoleKey.Enter:
            case ConsoleKey.Spacebar:
                CurrentMenu.SelectCurrentItem();
                break;
            case ConsoleKey.Escape:
            case ConsoleKey.Backspace:
                CloseCurrentMenu();
                break;
        }
    }

    public void Render()
    {
        if (CurrentMenu == null) return;

        Console.Clear();
        Console.WriteLine($"=== {CurrentMenu.Title} ===\n");

        for (int i = 0; i < CurrentMenu.Items.Count; i++)
        {
            var item = CurrentMenu.Items[i];
            var prefix = i == CurrentMenu.SelectedIndex ? "> " : "  ";
            var color = item.IsEnabled ? ConsoleColor.White : ConsoleColor.DarkGray;
            
            Console.ForegroundColor = color;
            Console.WriteLine($"{prefix}{item.Text}");
            Console.ResetColor();
        }

        Console.WriteLine("\n[Arrow Keys/WS: Navigate | Enter: Select | Esc: Back]");
    }
}
