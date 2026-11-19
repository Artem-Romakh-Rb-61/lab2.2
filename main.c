#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Прототипи функцій чисельного інтегрування (за шаблоном методички) */
double num_comput_integral_l_re(double left_boundary_a, double right_boundary_b, unsigned int intervals);
double num_comput_integral_r_re(double left_boundary_a, double right_boundary_b, unsigned int intervals);
double num_comput_integral_trap(double left_boundary_a, double right_boundary_b, unsigned int intervals);
double num_comput_integral_Simps(double left_boundary_a, double right_boundary_b, unsigned int intervals);

/* Прототип функції підінтегрального виразу для варіанту № 14 */
double integrand_expression(double x);

int main(void)
{
    /* Локальні змінні без використання глобальних (відповідно до вимог курсу) */
    double left_boundary_a = 0.0;
    double right_boundary_b = 0.0;
    double measurement_error = 0.0;
    double integral_s = 0.0;
    double I1 = 0.0, I2 = 0.0; /* Значення інтегралу для N та N + 2 для оцінки похибки */
    unsigned int intervals = 0;
    unsigned int var = 0;
    unsigned int i = 0;

    while (1)
    {
        /* Введення меж інтегрування та перевірка області визначення (x >= 0 для коренів) */
        printf("\n\tEnter the left boundary (a >= 0)\n\tX(first) = ");
        scanf("%lf", &left_boundary_a);

        printf("\n\tEnter the right boundary (b > a)\n\tX(last) = ");
        scanf("%lf", &right_boundary_b);

        if (left_boundary_a < 0.0 || right_boundary_b <= left_boundary_a)
        {
            printf("\n\tInvalid boundaries! Must satisfy 0 <= a < b.\n");
            continue;
        }

        /* Введення кількості проміжків розбиття з контролем коректності */
        do
        {
            printf("\tEnter the number of partition intervals (N > 0)\n\tN = ");
            scanf("%u", &intervals);
        } while (intervals == 0);

        /* Введення заданої точності (похибки) обчислення інтегралу */
        printf("\n\tEnter the measurement error of integration\n\tMeasurement error = ");
        scanf("%lf", &measurement_error);

        /* Вибір методу обчислення з валідацією номера варіанту через цикл */
        do
        {
            printf("\nChoose the method of calculating:\n");
            printf("\t1. By Left Rectangles\n");
            printf("\t2. By Right Rectangles\n");
            printf("\t3. By Trapezoidal method\n");
            printf("\t4. By Simpson's method (parabola method)\n");
            scanf("%u", &var);

            if (var < 1 || var > 4)
            {
                printf("\nYou are mistaken\n");
            }
        } while (var < 1 || var > 4);

        system("cls");

        switch (var)
        {
            case 1:
            {
                /* Обчислення значення інтегралу методом лівих прямокутників при заданому N */
                integral_s = num_comput_integral_l_re(left_boundary_a, right_boundary_b, intervals);

                /* Підбір кількості проміжків із кроком +2 до виконання умови |I1 - I2| <= eps */
                i = intervals;
                do
                {
                    I1 = num_comput_integral_l_re(left_boundary_a, right_boundary_b, i);
                    I2 = num_comput_integral_l_re(left_boundary_a, right_boundary_b, i + 2);
                    i += 2;
                } while (fabs(I1 - I2) > measurement_error);

                printf("\n\n\t* Left Rectangles method *\n");
                printf("\n\ta = %.2lf \n\tb = %.2lf \n\tIntegral (N = %u) = %.8lf \n\tIntegral (eps) = %.8lf \n\tN_opt = %u\n",
                       left_boundary_a, right_boundary_b, intervals, integral_s, I2, i);
            }
            break;

            case 2:
            {
                /* Обчислення значення інтегралу методом правих прямокутників при заданому N */
                integral_s = num_comput_integral_r_re(left_boundary_a, right_boundary_b, intervals);

                /* Послідовне збільшення N на 2 до досягнення заданої похибки */
                i = intervals;
                do
                {
                    I1 = num_comput_integral_r_re(left_boundary_a, right_boundary_b, i);
                    I2 = num_comput_integral_r_re(left_boundary_a, right_boundary_b, i + 2);
                    i += 2;
                } while (fabs(I1 - I2) > measurement_error);

                printf("\n\n\t* Right Rectangles method *\n");
                printf("\n\ta = %.2lf \n\tb = %.2lf \n\tIntegral (N = %u) = %.8lf \n\tIntegral (eps) = %.8lf \n\tN_opt = %u\n",
                       left_boundary_a, right_boundary_b, intervals, integral_s, I2, i);
            }
            break;

            case 3:
            {
                /* Обчислення значення інтегралу методом трапецій при заданому N */
                integral_s = num_comput_integral_trap(left_boundary_a, right_boundary_b, intervals);

                /* Послідовне збільшення N на 2 до досягнення заданої похибки */
                i = intervals;
                do
                {
                    I1 = num_comput_integral_trap(left_boundary_a, right_boundary_b, i);
                    I2 = num_comput_integral_trap(left_boundary_a, right_boundary_b, i + 2);
                    i += 2;
                } while (fabs(I1 - I2) > measurement_error);

                printf("\n\n\t* Trapezoidal method *\n");
                printf("\n\ta = %.2lf \n\tb = %.2lf \n\tIntegral (N = %u) = %.8lf \n\tIntegral (eps) = %.8lf \n\tN_opt = %u\n",
                       left_boundary_a, right_boundary_b, intervals, integral_s, I2, i);
            }
            break;

            case 4:
            {
                /* Метод Сімпсона коректно працює лише для парної кількості проміжків */
                if (intervals % 2 != 0)
                {
                    intervals++;
                }

                integral_s = num_comput_integral_Simps(left_boundary_a, right_boundary_b, intervals);

                /* Крок +2 зберігає парність кількості інтервалів на кожній ітерації */
                i = intervals;
                do
                {
                    I1 = num_comput_integral_Simps(left_boundary_a, right_boundary_b, i);
                    I2 = num_comput_integral_Simps(left_boundary_a, right_boundary_b, i + 2);
                    i += 2;
                } while (fabs(I1 - I2) > measurement_error);

                printf("\n\n\t* Simpson's method (parabola method) *\n");
                printf("\n\ta = %.2lf \n\tb = %.2lf \n\tIntegral (N = %u) = %.8lf \n\tIntegral (eps) = %.8lf \n\tN_opt = %u\n",
                       left_boundary_a, right_boundary_b, intervals, integral_s, I2, i);
            }
            break;
        }
    }

    return 0;
}

/* Метод лівих прямокутників: сумування значень у лівих точках кожного з N відрізків */
double num_comput_integral_l_re(double left_boundary_a, double right_boundary_b, unsigned int intervals)
{
    double integral_s = 0.0;
    double x = left_boundary_a;
    double h = (right_boundary_b - left_boundary_a) / intervals;
    unsigned int k;

    for (k = 0; k < intervals; k++)
    {
        integral_s += integrand_expression(x);
        x += h;
    }

    return integral_s * h;
}

/* Метод правих прямокутників: сумування значень у правих точках кожного з N відрізків */
double num_comput_integral_r_re(double left_boundary_a, double right_boundary_b, unsigned int intervals)
{
    double integral_s = 0.0;
    double h = (right_boundary_b - left_boundary_a) / intervals;
    double x = left_boundary_a + h;
    unsigned int k;

    for (k = 1; k <= intervals; k++)
    {
        integral_s += integrand_expression(x);
        x += h;
    }

    return integral_s * h;
}

/* Метод трапецій: півсума значень на краях плюс подвоєна сума у внутрішніх вузлах */
double num_comput_integral_trap(double left_boundary_a, double right_boundary_b, unsigned int intervals)
{
    double h = (right_boundary_b - left_boundary_a) / intervals;
    double sum_inner = 0.0;
    double x = 0.0;
    unsigned int k;

    for (k = 1; k < intervals; k++)
    {
        x = left_boundary_a + k * h;
        sum_inner += integrand_expression(x);
    }

    return (h / 2.0) * (integrand_expression(left_boundary_a) + integrand_expression(right_boundary_b) + 2.0 * sum_inner);
}

/* Метод парабол (Сімпсона): вагові коефіцієнти 4 для непарних вузлів і 2 для парних */
double num_comput_integral_Simps(double left_boundary_a, double right_boundary_b, unsigned int intervals)
{
    double h = (right_boundary_b - left_boundary_a) / intervals;
    double sum_odd = 0.0;
    double sum_even = 0.0;
    double x = 0.0;
    unsigned int k;

    for (k = 1; k < intervals; k++)
    {
        x = left_boundary_a + k * h;
        if (k % 2 != 0)
        {
            sum_odd += integrand_expression(x);
        }
        else
        {
            sum_even += integrand_expression(x);
        }
    }

    return (h / 3.0) * (integrand_expression(left_boundary_a) + integrand_expression(right_boundary_b) + 4.0 * sum_odd + 2.0 * sum_even);
}

/* Підінтегральна функція f(x) = sqrt(2 * x^3) + sqrt(x) (Варіант № 14) */
double integrand_expression(double x)
{
    return sqrt(2.0 * pow(x, 3.0)) + sqrt(x);
}
