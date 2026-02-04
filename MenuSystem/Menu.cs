namespace RPGMenuSystem.MenuSystem;

public class Menu
{
    public string Title { get; set; } = string.Empty;
    public List<MenuItem> Items { get; set; } = new();
    public int SelectedIndex { get; private set; } = 0;
    public Menu? ParentMenu { get; set; }

    public void NavigateUp()
    {
        if (SelectedIndex > 0)
            SelectedIndex--;
    }

    public void NavigateDown()
    {
        if (SelectedIndex < Items.Count - 1)
            SelectedIndex++;
    }

    public MenuItem GetSelectedItem()
    {
        return Items[SelectedIndex];
    }

    public void SelectCurrentItem()
    {
        var item = GetSelectedItem();
        if (item.IsEnabled)
        {
            item.OnSelect?.Invoke();
        }
    }
}
