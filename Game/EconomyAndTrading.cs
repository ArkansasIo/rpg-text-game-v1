namespace RPGMenuSystem.Game;

public class AuctionHouse
{
    public List<AuctionListing> Listings { get; set; } = new();
    private int _nextListingId = 1;
    
    public bool CreateListing(Player seller, AdvancedItem item, int buyoutPrice, int startingBid, int duration)
    {
        var listing = new AuctionListing
        {
            Id = _nextListingId++,
            SellerName = seller.Name,
            Item = item,
            BuyoutPrice = buyoutPrice,
            CurrentBid = startingBid,
            StartingBid = startingBid,
            TimeRemaining = duration,
            ListedAt = DateTime.Now
        };
        
        Listings.Add(listing);
        return true;
    }
    
    public bool PlaceBid(Player bidder, AuctionListing listing, int bidAmount)
    {
        if (bidAmount <= listing.CurrentBid) return false;
        if (bidder.Gold < bidAmount) return false;
        
        // Refund previous bidder
        if (listing.CurrentBidder != null)
        {
            // Return gold to previous bidder (would need player lookup)
        }
        
        listing.CurrentBid = bidAmount;
        listing.CurrentBidder = bidder.Name;
        return true;
    }
    
    public bool Buyout(Player buyer, AuctionListing listing)
    {
        if (buyer.Gold < listing.BuyoutPrice) return false;
        
        buyer.Gold -= listing.BuyoutPrice;
        buyer.Inventory.Add(new Item { Name = listing.Item.Name, Value = listing.Item.Value });
        
        Listings.Remove(listing);
        return true;
    }
    
    public List<AuctionListing> Search(string query, ItemType? type = null, int? minLevel = null, int? maxLevel = null)
    {
        var results = Listings.AsEnumerable();
        
        if (!string.IsNullOrEmpty(query))
        {
            results = results.Where(l => l.Item.Name.Contains(query, StringComparison.OrdinalIgnoreCase));
        }
        
        if (type.HasValue)
        {
            results = results.Where(l => l.Item.Type == type.Value);
        }
        
        if (minLevel.HasValue)
        {
            results = results.Where(l => l.Item.RequiredLevel >= minLevel.Value);
        }
        
        if (maxLevel.HasValue)
        {
            results = results.Where(l => l.Item.RequiredLevel <= maxLevel.Value);
        }
        
        return results.ToList();
    }
}

public class AuctionListing
{
    public int Id { get; set; }
    public string SellerName { get; set; } = string.Empty;
    public AdvancedItem Item { get; set; } = null!;
    public int BuyoutPrice { get; set; }
    public int StartingBid { get; set; }
    public int CurrentBid { get; set; }
    public string? CurrentBidder { get; set; }
    public int TimeRemaining { get; set; } // in seconds
    public DateTime ListedAt { get; set; }
}

public class MailSystem
{
    public List<Mail> Inbox { get; set; } = new();
    public List<Mail> Sent { get; set; } = new();
    private int _nextMailId = 1;
    
    public bool SendMail(string senderName, string recipientName, string subject, string body, int gold = 0, AdvancedItem? attachment = null)
    {
        var mail = new Mail
        {
            Id = _nextMailId++,
            SenderName = senderName,
            RecipientName = recipientName,
            Subject = subject,
            Body = body,
            Gold = gold,
            Attachment = attachment,
            SentAt = DateTime.Now,
            IsRead = false
        };
        
        Inbox.Add(mail);
        return true;
    }
    
    public void ReadMail(Mail mail)
    {
        mail.IsRead = true;
    }
    
    public void DeleteMail(Mail mail)
    {
        Inbox.Remove(mail);
    }
    
    public int GetUnreadCount()
    {
        return Inbox.Count(m => !m.IsRead);
    }
}

public class Mail
{
    public int Id { get; set; }
    public string SenderName { get; set; } = string.Empty;
    public string RecipientName { get; set; } = string.Empty;
    public string Subject { get; set; } = string.Empty;
    public string Body { get; set; } = string.Empty;
    public int Gold { get; set; }
    public AdvancedItem? Attachment { get; set; }
    public DateTime SentAt { get; set; }
    public bool IsRead { get; set; }
    public bool HasAttachment => Attachment != null || Gold > 0;
}

public class TransmogSystem
{
    public Dictionary<EquipmentSlotType, AdvancedItem?> TransmoggedAppearances { get; set; } = new();
    public List<int> UnlockedAppearances { get; set; } = new();
    
    public bool UnlockAppearance(AdvancedItem item)
    {
        if (!UnlockedAppearances.Contains(item.Id))
        {
            UnlockedAppearances.Add(item.Id);
            return true;
        }
        return false;
    }
    
    public bool ApplyTransmog(EquipmentSlotType slot, AdvancedItem appearance)
    {
        if (!UnlockedAppearances.Contains(appearance.Id)) return false;
        
        TransmoggedAppearances[slot] = appearance;
        return true;
    }
    
    public void RemoveTransmog(EquipmentSlotType slot)
    {
        TransmoggedAppearances.Remove(slot);
    }
}

public class ResourceNode
{
    public int Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public ResourceType Type { get; set; }
    public int RequiredSkill { get; set; }
    public List<ResourceDrop> PossibleDrops { get; set; } = new();
    public int RespawnTime { get; set; } = 300; // seconds
    public bool IsActive { get; set; } = true;
    public Vector3 Position { get; set; }
    
    public List<AdvancedItem> Gather(int playerSkill)
    {
        if (playerSkill < RequiredSkill) return new List<AdvancedItem>();
        if (!IsActive) return new List<AdvancedItem>();
        
        var gathered = new List<AdvancedItem>();
        var random = new Random();
        
        foreach (var drop in PossibleDrops)
        {
            if (random.NextDouble() < drop.DropChance)
            {
                // Create item (simplified)
                gathered.Add(new AdvancedItem { Name = drop.ItemName });
            }
        }
        
        IsActive = false;
        return gathered;
    }
}

public enum ResourceType
{
    Herb,
    Ore,
    Fish,
    Wood,
    Treasure
}

public class ResourceDrop
{
    public string ItemName { get; set; } = string.Empty;
    public float DropChance { get; set; } = 0.5f;
    public int MinQuantity { get; set; } = 1;
    public int MaxQuantity { get; set; } = 1;
}

public class FishingSystem
{
    public int FishingSkill { get; set; }
    public bool IsFishing { get; set; }
    public float CastTime { get; set; }
    public float BiteChance { get; set; }
    
    public void StartFishing()
    {
        IsFishing = true;
        CastTime = 0;
        BiteChance = 0.01f + (FishingSkill * 0.001f);
    }
    
    public AdvancedItem? CheckForCatch()
    {
        var random = new Random();
        if (random.NextDouble() < BiteChance)
        {
            return GenerateFish();
        }
        return null;
    }
    
    private AdvancedItem GenerateFish()
    {
        var fish = new List<string> { "Salmon", "Trout", "Bass", "Catfish", "Pike", "Rare Golden Fish" };
        var random = new Random();
        
        return new AdvancedItem
        {
            Name = fish[random.Next(fish.Count)],
            Type = ItemType.Consumable,
            Value = 10 + FishingSkill
        };
    }
}

public class ThreatSystem
{
    public Dictionary<string, int> ThreatTable { get; set; } = new();
    
    public void AddThreat(string targetName, int amount)
    {
        if (!ThreatTable.ContainsKey(targetName))
        {
            ThreatTable[targetName] = 0;
        }
        ThreatTable[targetName] += amount;
    }
    
    public void ModifyThreat(string targetName, float multiplier)
    {
        if (ThreatTable.ContainsKey(targetName))
        {
            ThreatTable[targetName] = (int)(ThreatTable[targetName] * multiplier);
        }
    }
    
    public string? GetHighestThreatTarget()
    {
        if (ThreatTable.Count == 0) return null;
        return ThreatTable.OrderByDescending(kvp => kvp.Value).First().Key;
    }
    
    public void RemoveThreat(string targetName)
    {
        ThreatTable.Remove(targetName);
    }
    
    public void ClearThreat()
    {
        ThreatTable.Clear();
    }
}

public class ComboSystem
{
    public int CurrentComboCount { get; private set; }
    public float ComboTimer { get; private set; }
    public float ComboWindow { get; set; } = 3f;
    public int MaxCombo { get; set; } = 10;
    
    public void AddCombo()
    {
        if (CurrentComboCount < MaxCombo)
        {
            CurrentComboCount++;
        }
        ComboTimer = ComboWindow;
    }
    
    public void Update(float deltaTime)
    {
        if (ComboTimer > 0)
        {
            ComboTimer -= deltaTime;
            if (ComboTimer <= 0)
            {
                ResetCombo();
            }
        }
    }
    
    public void ResetCombo()
    {
        CurrentComboCount = 0;
        ComboTimer = 0;
    }
    
    public float GetComboDamageMultiplier()
    {
        return 1.0f + (CurrentComboCount * 0.1f);
    }
}
