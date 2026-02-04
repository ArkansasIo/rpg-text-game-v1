namespace RPGMenuSystem.MenuSystem;

public class MenuItem
{
    public string Text { get; set; } = string.Empty;
    public Action? OnSelect { get; set; }
    public Menu? SubMenu { get; set; }
    public bool IsEnabled { get; set; } = true;
}
