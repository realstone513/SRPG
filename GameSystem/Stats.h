#pragma once

enum class StatsEnum
{
	Health,
	Damage,
	Armor,
};

class Stats
{
public:
	int		baseHealth;
	int		baseDamage;
	int		baseArmor;
	int		baseRange;
	int		baseMobility;
	bool	rangeFill;

	int		AddHealth;
	int		AddDamage;
	int		AddArmor;
	int		AddRange;
	int		AddMobility;

	int		modifyHealth;
	int		modifyDamage;
	int		modifyArmor;
	int		modifyRange;
	int		modifyMobility;

	int		currentHealth;

	Stats() {};
	~Stats() {};

	void SetBaseStats(int h, int d, int a, int r, int m, bool f = true)
	{
		baseHealth = h;
		baseDamage = d;
		baseArmor = a;
		baseRange = r;
		baseMobility = m;
		rangeFill = f;
		SetModifyStats();
	}

	void SetAddStats(int h, int d, int a, int r, int m)
	{
		AddHealth = h;
		AddDamage = d;
		AddArmor = a;
		AddRange = r;
		AddMobility = m;
		SetModifyStats();
	}

	void UpdateBaseStats(int h, int d, int a, int r, int m, bool f = true)
	{
		baseHealth += h;
		baseDamage += d;
		baseArmor += a;
		baseRange += r;
		baseMobility += m;
		rangeFill = f;
		SetModifyStats();
	}

	void UpdateAddStats(int h, int d, int a, int r, int m)
	{
		AddHealth += h;
		AddDamage += d;
		AddArmor += a;
		AddRange += r;
		AddMobility += m;
		SetModifyStats();
	}

	void SetModifyStats()
	{
		modifyHealth = baseHealth + AddHealth;
		modifyDamage = baseDamage + AddDamage;
		modifyArmor = baseArmor + AddArmor;
		modifyRange = baseRange + AddRange;
		modifyMobility = baseMobility + AddMobility;
	}

	void ResetStats()
	{
		SetAddStats(0, 0, 0, 0, 0);
		SetFullCurrentHealth();
	}

	void SetFullCurrentHealth()
	{
		currentHealth = modifyHealth;
	}
};