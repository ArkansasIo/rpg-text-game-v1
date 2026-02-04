namespace RPGMenuSystem.Game;

public enum WeatherType
{
    Clear,
    Cloudy,
    Rainy,
    Stormy,
    Snowy,
    Foggy,
    Sandstorm,
    Windy,
    Hail,
    Ash
}

public class WeatherSystem
{
    public WeatherType CurrentWeather { get; private set; } = WeatherType.Clear;
    public float WeatherIntensity { get; private set; } = 0f;
    public float TimeUntilChange { get; private set; } = 300f;
    
    public void Update(float deltaTime)
    {
        TimeUntilChange -= deltaTime;
        
        if (TimeUntilChange <= 0)
        {
            ChangeWeather();
            TimeUntilChange = new Random().Next(300, 600); // 5-10 minutes
        }
    }
    
    private void ChangeWeather()
    {
        var random = new Random();
        CurrentWeather = (WeatherType)random.Next(0, Enum.GetValues(typeof(WeatherType)).Length);
        WeatherIntensity = (float)random.NextDouble();
    }
    
    public Dictionary<string, float> GetWeatherEffects()
    {
        var effects = new Dictionary<string, float>();
        
        switch (CurrentWeather)
        {
            case WeatherType.Rainy:
                effects["WaterDamage"] = -0.2f;
                effects["FireDamage"] = -0.1f;
                effects["Visibility"] = -0.3f;
                break;
            case WeatherType.Stormy:
                effects["LightningDamage"] = 0.2f;
                effects["Visibility"] = -0.5f;
                break;
            case WeatherType.Snowy:
                effects["FrostDamage"] = 0.2f;
                effects["FireDamage"] = -0.2f;
                effects["MovementSpeed"] = -0.1f;
                break;
            case WeatherType.Foggy:
                effects["Visibility"] = -0.7f;
                effects["ShadowDamage"] = 0.1f;
                break;
            case WeatherType.Sandstorm:
                effects["PhysicalDamage"] = -0.1f;
                effects["Visibility"] = -0.6f;
                break;
        }
        
        return effects;
    }
}

public enum TimeOfDay
{
    Dawn,
    Morning,
    Noon,
    Afternoon,
    Dusk,
    Night,
    Midnight
}

public class DayNightSystem
{
    public float CurrentTime { get; private set; } = 12f; // 0-24 hours
    public float TimeSpeed { get; set; } = 60f; // 1 real second = 60 game seconds (1 minute)
    public int CurrentDay { get; private set; } = 1;
    
    public void Update(float deltaTime)
    {
        CurrentTime += (deltaTime * TimeSpeed) / 3600f; // Convert to game hours
        
        if (CurrentTime >= 24f)
        {
            CurrentTime -= 24f;
            CurrentDay++;
        }
    }
    
    public TimeOfDay GetTimeOfDay()
    {
        if (CurrentTime >= 5 && CurrentTime < 7) return TimeOfDay.Dawn;
        if (CurrentTime >= 7 && CurrentTime < 12) return TimeOfDay.Morning;
        if (CurrentTime >= 12 && CurrentTime < 14) return TimeOfDay.Noon;
        if (CurrentTime >= 14 && CurrentTime < 18) return TimeOfDay.Afternoon;
        if (CurrentTime >= 18 && CurrentTime < 20) return TimeOfDay.Dusk;
        if (CurrentTime >= 20 && CurrentTime < 23) return TimeOfDay.Night;
        return TimeOfDay.Midnight;
    }
    
    public float GetLightLevel()
    {
        var timeOfDay = GetTimeOfDay();
        return timeOfDay switch
        {
            TimeOfDay.Noon => 1.0f,
            TimeOfDay.Morning => 0.8f,
            TimeOfDay.Afternoon => 0.9f,
            TimeOfDay.Dawn => 0.5f,
            TimeOfDay.Dusk => 0.5f,
            TimeOfDay.Night => 0.2f,
            TimeOfDay.Midnight => 0.1f,
            _ => 1.0f
        };
    }
    
    public Dictionary<string, float> GetTimeEffects()
    {
        var effects = new Dictionary<string, float>();
        var timeOfDay = GetTimeOfDay();
        
        switch (timeOfDay)
        {
            case TimeOfDay.Night:
            case TimeOfDay.Midnight:
                effects["ShadowDamage"] = 0.2f;
                effects["UndeadPower"] = 0.3f;
                effects["Stealth"] = 0.2f;
                break;
            case TimeOfDay.Noon:
                effects["HolyDamage"] = 0.2f;
                effects["UndeadWeakness"] = 0.2f;
                break;
            case TimeOfDay.Dawn:
            case TimeOfDay.Dusk:
                effects["NatureDamage"] = 0.1f;
                break;
        }
        
        return effects;
    }
    
    public string GetTimeString()
    {
        int hours = (int)CurrentTime;
        int minutes = (int)((CurrentTime - hours) * 60);
        return $"{hours:D2}:{minutes:D2}";
    }
}

public class EnvironmentalHazard
{
    public string Name { get; set; } = string.Empty;
    public string Description { get; set; } = string.Empty;
    public int DamagePerSecond { get; set; }
    public string DamageType { get; set; } = "Environmental";
    public List<StatusEffect> AppliedEffects { get; set; } = new();
}

public class WorldEventSystem
{
    public List<WorldEvent> ActiveEvents { get; set; } = new();
    public List<WorldEvent> ScheduledEvents { get; set; } = new();
    
    public void Update(float deltaTime)
    {
        foreach (var evt in ActiveEvents.ToList())
        {
            evt.RemainingTime -= deltaTime;
            if (evt.RemainingTime <= 0)
            {
                EndEvent(evt);
            }
        }
        
        foreach (var evt in ScheduledEvents.ToList())
        {
            evt.TimeUntilStart -= deltaTime;
            if (evt.TimeUntilStart <= 0)
            {
                StartEvent(evt);
            }
        }
    }
    
    public void StartEvent(WorldEvent evt)
    {
        evt.IsActive = true;
        evt.RemainingTime = evt.Duration;
        ActiveEvents.Add(evt);
        ScheduledEvents.Remove(evt);
    }
    
    public void EndEvent(WorldEvent evt)
    {
        evt.IsActive = false;
        ActiveEvents.Remove(evt);
    }
}

public class WorldEvent
{
    public int Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public string Description { get; set; } = string.Empty;
    public bool IsActive { get; set; }
    public float Duration { get; set; }
    public float RemainingTime { get; set; }
    public float TimeUntilStart { get; set; }
    public List<int> AffectedZones { get; set; } = new();
    public Dictionary<string, int> Rewards { get; set; } = new();
    
    public static List<WorldEvent> GetScheduledEvents()
    {
        return new List<WorldEvent>
        {
            new WorldEvent { Id = 1, Name = "Meteor Shower", Description = "Meteors rain from the sky", Duration = 600, TimeUntilStart = 3600 },
            new WorldEvent { Id = 2, Name = "Goblin Invasion", Description = "Goblins attack settlements", Duration = 1800, TimeUntilStart = 7200 },
            new WorldEvent { Id = 3, Name = "Dragon Attack", Description = "An ancient dragon terrorizes the land", Duration = 1200, TimeUntilStart = 10800 },
            new WorldEvent { Id = 4, Name = "Blood Moon", Description = "The moon turns red, empowering dark forces", Duration = 3600, TimeUntilStart = 86400 },
            new WorldEvent { Id = 5, Name = "Harvest Festival", Description = "Celebration with bonus rewards", Duration = 7200, TimeUntilStart = 5400 }
        };
    }
}
