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

	int		additionalHealth;
	int		additionalDamage;
	int		additionalArmor;
	int		additionalRange;
	int		additionalMobility;

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
		additionalHealth = h;
		additionalDamage = d;
		additionalArmor = a;
		additionalRange = r;
		additionalMobility = m;
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
		additionalHealth += h;
		additionalDamage += d;
		additionalArmor += a;
		additionalRange += r;
		additionalMobility += m;
		SetModifyStats();
	}

	void SetModifyStats()
	{
		modifyHealth = baseHealth + additionalHealth;
		modifyDamage = baseDamage + additionalDamage;
		modifyArmor = baseArmor + additionalArmor;
		modifyRange = baseRange + additionalRange;
		modifyMobility = baseMobility + additionalMobility;
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