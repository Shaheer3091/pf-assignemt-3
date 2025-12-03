#include <stdio.h>

double calculateRepayment(double loan, double rate, double installment, int year, int totalYears) {
    if (loan <= 0 || year > totalYears) {
        return 0;
    }

    
    loan = loan + (loan * rate / 100.0);

    
    double remainingLoan = loan - installment;
    if (remainingLoan < 0) remainingLoan = 0;

    printf("Year %d: Remaining loan = %.2f\n", year, remainingLoan);

    
    return installment + calculateRepayment(remainingLoan, rate, installment, year + 1, totalYears);
}

int main() {
    double loan = 100000;
    double rate = 5;
    int years = 3;

    // for demonstration , installment has been set to 35000
    double installment = 35000;

    printf("Repayment Schedule:\n");
    double totalPaid = calculateRepayment(loan, rate, installment, 1, years);

    printf("\nTotal repayment over %d years = %.2f\n", years, totalPaid);

    return 0;
}
