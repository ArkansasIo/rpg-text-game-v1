namespace RPGMenuSystem.Game;

public enum StatusEffectType
{
    Buff,
    Debuff,
    DamageOverTime,
    HealOverTime,
    CrowdControl
}

public enum CCType
{
    None,
    Stun,
    Root,
    Silence,
    Fear,
    Charm,
    Sleep,
    Slow,
    Snare
}

public class StatusEffect
{
    public int Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public string Description { get; set; } = string.Empty;
    public StatusEffectType Type { get; set; }
    public CCType CrowdControl { get; set; } = CCType.None;
    public float Duration { get; set; }
    public float RemainingTime { get; set; }
    public int StackCount { get; set; } = 1;
    public int MaxStacks { get; set; } = 1;
    public bool IsPermanent { get; set; }
    public string IconPath { get; set; } = string.Empty;
    
    // Effect values
    public Dictionary<string, float> StatModifiers { get; set; } = new();
    public int DamagePerTick { get; set; }
    public int HealPerTick { get; set; }
    public float TickInterval { get; set; } = 3f;
    public float NextTick { get; set; }
    
    // Source info
    public string SourceName { get; set; } = string.Empty;
    public bool IsDispellable { get; set; } = true;
    
    public void Update(float deltaTime)
    {
        if (!IsPermanent)
        {
            RemainingTime -= deltaTime;
        }
        
        NextTick -= deltaTime;
        if (NextTick <= 0)
        {
            NextTick = TickInterval;
        }
    }
    
    public bool IsExpired()
    {
        return !IsPermanent && RemainingTime <= 0;
    }
}

public class StatusEffectManager
{
    public List<StatusEffect> ActiveEffects { get; set; } = new();
    
    public void AddEffect(StatusEffect effect)
    {
        var existing = ActiveEffects.FirstOrDefault(e => e.Id == effect.Id && e.SourceName == effect.SourceName);
        
        if (existing != null)
        {
            if (existing.StackCount < existing.MaxStacks)
            {
                existing.StackCount++;
            }
            // Refresh duration
            existing.RemainingTime = effect.Duration;
        }
        else
        {
            effect.RemainingTime = effect.Duration;
            effect.NextTick = effect.TickInterval;
            ActiveEffects.Add(effect);
        }
    }
    
    public void RemoveEffect(int effectId)
    {
        ActiveEffects.RemoveAll(e => e.Id == effectId);
    }
    
    public void RemoveEffectsByType(StatusEffectType type)
    {
        ActiveEffects.RemoveAll(e => e.Type == type);
    }
    
    public void Dispel(int count = 1)
    {
        var dispellable = ActiveEffects.Where(e => e.IsDispellable && e.Type == StatusEffectType.Debuff).Take(count).ToList();
        foreach (var effect in dispellable)
        {
            ActiveEffects.Remove(effect);
        }
    }
    
    public void Update(float deltaTime)
    {
        foreach (var effect in ActiveEffects.ToList())
        {
            effect.Update(deltaTime);
            
            if (effect.IsExpired())
            {
                ActiveEffects.Remove(effect);
            }
        }
    }
    
    public Dictionary<string, float> GetTotalStatModifiers()
    {
        var stats = new Dictionary<string, float>();
        
        foreach (var effect in ActiveEffects)
        {
            foreach (var stat in effect.StatModifiers)
            {
                if (!stats.ContainsKey(stat.Key))
                    stats[stat.Key] = 0;
                stats[stat.Key] += stat.Value * effect.StackCount;
            }
        }
        
        return stats;
    }
    
    public int GetTotalDotDamage()
    {
        return ActiveEffects.Where(e => e.NextTick <= 0).Sum(e => e.DamagePerTick);
    }
    
    public int GetTotalHotHealing()
    {
        return ActiveEffects.Where(e => e.NextTick <= 0).Sum(e => e.HealPerTick);
    }
    
    public bool HasCrowdControl()
    {
        return ActiveEffects.Any(e => e.CrowdControl != CCType.None);
    }
    
    public bool CanAct()
    {
        return !ActiveEffects.Any(e => e.CrowdControl == CCType.Stun || 
                                       e.CrowdControl == CCType.Fear || 
                                       e.CrowdControl == CCType.Sleep ||
                                       e.CrowdControl == CCType.Charm);
    }
    
    public bool CanCast()
    {
        return !ActiveEffects.Any(e => e.CrowdControl == CCType.Silence);
    }
    
    public bool CanMove()
    {
        return !ActiveEffects.Any(e => e.CrowdControl == CCType.Root || 
                                       e.CrowdControl == CCType.Stun);
    }
    
    // Predefined status effects
    public static StatusEffect CreatePoison(int damage, float duration)
    {
        return new StatusEffect
        {
            Id = 1,
            Name = "Poison",
            Description = $"Takes {damage} damage every 3 seconds",
            Type = StatusEffectType.DamageOverTime,
            Duration = duration,
            DamagePerTick = damage,
            TickInterval = 3f,
            MaxStacks = 5,
            SourceName = "Poison"
        };
    }
    
    public static StatusEffect CreateBleed(int damage, float duration)
    {
        return new StatusEffect
        {
            Id = 2,
            Name = "Bleed",
            Description = $"Bleeding for {damage} damage every 2 seconds",
            Type = StatusEffectType.DamageOverTime,
            Duration = duration,
            DamagePerTick = damage,
            TickInterval = 2f,
            SourceName = "Bleed"
        };
    }
    
    public static StatusEffect CreateRegeneration(int healing, float duration)
    {
        return new StatusEffect
        {
            Id = 3,
            Name = "Regeneration",
            Description = $"Restores {healing} health every 5 seconds",
            Type = StatusEffectType.HealOverTime,
            Duration = duration,
            HealPerTick = healing,
            TickInterval = 5f,
            SourceName = "Regeneration"
        };
    }
    
    public static StatusEffect CreateHaste(float percentage, float duration)
    {
        return new StatusEffect
        {
            Id = 4,
            Name = "Haste",
            Description = $"Attack and cast speed increased by {percentage}%",
            Type = StatusEffectType.Buff,
            Duration = duration,
            StatModifiers = new Dictionary<string, float> { { "Haste", percentage } },
            SourceName = "Haste"
        };
    }
    
    public static StatusEffect CreateStun(float duration)
    {
        return new StatusEffect
        {
            Id = 5,
            Name = "Stunned",
            Description = "Cannot move or act",
            Type = StatusEffectType.CrowdControl,
            CrowdControl = CCType.Stun,
            Duration = duration,
            SourceName = "Stun"
        };
    }
    
    public static StatusEffect CreateSlow(float percentage, float duration)
    {
        return new StatusEffect
        {
            Id = 6,
            Name = "Slow",
            Description = $"Movement speed reduced by {percentage}%",
            Type = StatusEffectType.Debuff,
            CrowdControl = CCType.Slow,
            Duration = duration,
            StatModifiers = new Dictionary<string, float> { { "MovementSpeed", -percentage } },
            SourceName = "Slow"
        };
    }
    
    public static StatusEffect CreateShield(int amount, float duration)
    {
        return new StatusEffect
        {
            Id = 7,
            Name = "Shield",
            Description = $"Absorbs {amount} damage",
            Type = StatusEffectType.Buff,
            Duration = duration,
            StatModifiers = new Dictionary<string, float> { { "Shield", amount } },
            SourceName = "Shield"
        };
    }
    
    public static StatusEffect CreateStrengthBuff(int amount, float duration)
    {
        return new StatusEffect
        {
            Id = 8,
            Name = "Strength",
            Description = $"Strength increased by {amount}",
            Type = StatusEffectType.Buff,
            Duration = duration,
            StatModifiers = new Dictionary<string, float> { { "Strength", amount } },
            SourceName = "Strength Buff"
        };
    }
}
