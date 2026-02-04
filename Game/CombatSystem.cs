namespace RPGMenuSystem.Game;

public class Enemy
{
    public string Name { get; set; } = string.Empty;
    public int Health { get; set; }
    public int MaxHealth { get; set; }
    public int Attack { get; set; }
    public int Defense { get; set; }
    public int XPReward { get; set; }
    public int GoldReward { get; set; }
    public List<Item> PossibleDrops { get; set; } = new();

    public bool IsAlive => Health > 0;

    public int TakeDamage(int damage)
    {
        int actualDamage = Math.Max(1, damage - Defense);
        Health = Math.Max(0, Health - actualDamage);
        return actualDamage;
    }

    public int AttackPlayer()
    {
        Random rand = new Random();
        return Attack + rand.Next(-2, 3);
    }
}

public class CombatSystem
{
    private Enemy? _currentEnemy;
    private Random _random = new Random();

    public Enemy? CurrentEnemy => _currentEnemy;

    public Enemy GenerateRandomEnemy()
    {
        var enemyTypes = new[]
        {
            new Enemy 
            { 
                Name = "Goblin", 
                Health = 30, 
                MaxHealth = 30, 
                Attack = 8, 
                Defense = 2, 
                XPReward = 50, 
                GoldReward = 20,
                PossibleDrops = new List<Item> { new Item { Name = "Goblin Ear", Description = "Trophy from a goblin", Value = 5 } }
            },
            new Enemy 
            { 
                Name = "Wolf", 
                Health = 40, 
                MaxHealth = 40, 
                Attack = 12, 
                Defense = 3, 
                XPReward = 75, 
                GoldReward = 15,
                PossibleDrops = new List<Item> { new Item { Name = "Wolf Pelt", Description = "Soft wolf fur", Value = 25 } }
            },
            new Enemy 
            { 
                Name = "Bandit", 
                Health = 50, 
                MaxHealth = 50, 
                Attack = 15, 
                Defense = 5, 
                XPReward = 100, 
                GoldReward = 50,
                PossibleDrops = new List<Item> { new Item { Name = "Bandit's Dagger", Description = "A sharp dagger", Value = 40 } }
            },
            new Enemy 
            { 
                Name = "Orc", 
                Health = 70, 
                MaxHealth = 70, 
                Attack = 20, 
                Defense = 8, 
                XPReward = 150, 
                GoldReward = 75,
                PossibleDrops = new List<Item> { new Item { Name = "Orc Tooth", Description = "Large and sharp", Value = 30 } }
            },
            new Enemy 
            { 
                Name = "Ancient Dragon", 
                Health = 200, 
                MaxHealth = 200, 
                Attack = 40, 
                Defense = 15, 
                XPReward = 1000, 
                GoldReward = 500,
                PossibleDrops = new List<Item> { new Item { Name = "Dragon Scale", Description = "Legendary material", Value = 500 } }
            }
        };

        _currentEnemy = enemyTypes[_random.Next(enemyTypes.Length)];
        return _currentEnemy;
    }

    public CombatResult PlayerAttack(Player player)
    {
        if (_currentEnemy == null || !_currentEnemy.IsAlive)
            return new CombatResult { Message = "No enemy to attack!" };

        int playerDamage = player.GetTotalAttack() + _random.Next(-3, 5);
        int actualDamage = _currentEnemy.TakeDamage(playerDamage);

        string message = $"You attack {_currentEnemy.Name} for {actualDamage} damage!";

        if (!_currentEnemy.IsAlive)
        {
            player.GainExperience(_currentEnemy.XPReward);
            player.Gold += _currentEnemy.GoldReward;
            message += $"\n{_currentEnemy.Name} defeated! You gained {_currentEnemy.XPReward} XP and {_currentEnemy.GoldReward} gold!";

            if (_random.Next(100) < 30 && _currentEnemy.PossibleDrops.Count > 0)
            {
                var drop = _currentEnemy.PossibleDrops[_random.Next(_currentEnemy.PossibleDrops.Count)];
                player.Inventory.Add(drop);
                message += $"\n{_currentEnemy.Name} dropped {drop.Name}!";
            }

            return new CombatResult { Message = message, CombatEnded = true, PlayerWon = true };
        }

        int enemyDamage = _currentEnemy.AttackPlayer();
        int playerActualDamage = player.TakeDamage(enemyDamage);
        message += $"\n{_currentEnemy.Name} attacks you for {playerActualDamage} damage!";

        if (!player.IsAlive)
        {
            message += "\nYou have been defeated!";
            return new CombatResult { Message = message, CombatEnded = true, PlayerWon = false };
        }

        return new CombatResult { Message = message };
    }

    public CombatResult PlayerDefend(Player player)
    {
        if (_currentEnemy == null || !_currentEnemy.IsAlive)
            return new CombatResult { Message = "No enemy to defend against!" };

        string message = "You take a defensive stance!";
        
        int enemyDamage = _currentEnemy.AttackPlayer();
        int reducedDamage = Math.Max(1, (enemyDamage - player.GetTotalDefense()) / 2);
        player.Health = Math.Max(0, player.Health - reducedDamage);
        
        message += $"\n{_currentEnemy.Name} attacks but you defend! Only {reducedDamage} damage taken!";

        if (!player.IsAlive)
        {
            message += "\nYou have been defeated!";
            return new CombatResult { Message = message, CombatEnded = true, PlayerWon = false };
        }

        return new CombatResult { Message = message };
    }

    public CombatResult PlayerFlee()
    {
        int fleeChance = _random.Next(100);
        if (fleeChance < 60)
        {
            return new CombatResult { Message = "You successfully fled from battle!", CombatEnded = true };
        }
        else
        {
            return new CombatResult { Message = "Failed to flee! The enemy blocks your escape!" };
        }
    }

    public void EndCombat()
    {
        _currentEnemy = null;
    }
}

public class CombatResult
{
    public string Message { get; set; } = string.Empty;
    public bool CombatEnded { get; set; }
    public bool PlayerWon { get; set; }
}
