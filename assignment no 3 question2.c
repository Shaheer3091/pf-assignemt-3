#include <stdio.h>

void calculateFuel(int currentFuel, int fuelConsumption, int fuelRecharge, int solarRechargeBonus, int currentPlanet, int totalPlanets) {
    if (currentFuel <= 0) {
        printf("Fuel finished before reaching all planets\n");
        return;
    }

    if (currentPlanet > totalPlanets) {
        printf("Journey completed successfully\n");
        return;
    }

    currentFuel = currentFuel - fuelConsumption;

    if (currentFuel < 0) {
        currentFuel = 0;
    }

    if (currentPlanet % 2 == 0) {
        currentFuel = currentFuel + fuelRecharge;
    }

    if (currentPlanet % 4 == 0) {
        currentFuel = currentFuel + solarRechargeBonus;
    }

    printf("Planet %d: Fuel Remaining = %d\n", currentPlanet, currentFuel);

    calculateFuel(currentFuel, fuelConsumption, fuelRecharge, solarRechargeBonus, currentPlanet + 1, totalPlanets);
}

int main() {
    int startingFuel;
    int fuelConsumption;
    int fuelRecharge;
    int solarRechargeBonus;
    int totalPlanets;

    printf("Enter starting fuel: ");
    scanf("%d", &startingFuel);

    printf("Enter fuel consumption at each planet: ");
    scanf("%d", &fuelConsumption);

    printf("Enter fuel recharge in gravitational zones: ");
    scanf("%d", &fuelRecharge);

    printf("Enter solar recharge bonus: ");
    scanf("%d", &solarRechargeBonus);

    printf("Enter total number of planets: ");
    scanf("%d", &totalPlanets);

    calculateFuel(startingFuel, fuelConsumption, fuelRecharge, solarRechargeBonus, 1, totalPlanets);

    return 0;
}
