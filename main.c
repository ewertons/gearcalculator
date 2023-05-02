#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

static void calculateGearsWithFixedAddendum(
    float gear1RootCircleDiameter, float gear1AddendumCircleDiameter,
    float pressureAngle)
{
    float module = (gear1AddendumCircleDiameter - gear1RootCircleDiameter)/4.5;
    float gear1PitchCircleDiameter = gear1AddendumCircleDiameter - 2 * module;
    float gear1NumberOfTeeth = gear1PitchCircleDiameter / module;

    if ((int)gear1NumberOfTeeth != gear1NumberOfTeeth)
    {
        printf("Module %f results in gear 1 fractional number of teeth: %f\r\n", module, gear1NumberOfTeeth);
        double gear1NumberOfTeethInteger, gear1NumberOfTeethFractional;

        gear1NumberOfTeethFractional = modf((double)gear1NumberOfTeeth, &gear1NumberOfTeethInteger);

        if (gear1NumberOfTeethFractional <= 0.5)
        {
            gear1NumberOfTeeth = (float)gear1NumberOfTeethInteger;
        }
        else
        {
            gear1NumberOfTeeth = (float)gear1NumberOfTeethInteger + 1;
        }

        module = gear1AddendumCircleDiameter / (gear1NumberOfTeeth + 2);
        gear1PitchCircleDiameter = gear1AddendumCircleDiameter - 2 * module;

        printf("Adjusted gear 1 number of teeth: %f\r\n", gear1NumberOfTeeth);
        printf("Adjusted module: %f\r\n", module);
        printf("Root circle diameter: argument=%f, adjusted=%f\r\n",
            gear1RootCircleDiameter, gear1PitchCircleDiameter - 2 * 1.25 * module);
        printf("Addendum circle diameter: argument=%f, adjusted=%f\r\n",
            gear1AddendumCircleDiameter, gear1PitchCircleDiameter + 2 * module);

        gear1RootCircleDiameter = gear1PitchCircleDiameter - 2 * 1.25 * module;
    }

    float dedendum = 1.25 * module;
    float teethWholeDepth = module + dedendum;
    float pressureAngleRadians = M_PI * pressureAngle / 180;
    double cosOfPressureAndleRadians = cos((double)pressureAngleRadians);

    float gear1ClearanceCircleDiameter = gear1PitchCircleDiameter - 2 * module;
    float gear1BaseCircleDiameter = gear1PitchCircleDiameter * cosOfPressureAndleRadians;
    gear1PitchCircleDiameter = gear1AddendumCircleDiameter - 2 * module;

    printf("\r\nmodule=%f\r\n", module);
    printf("pressure angle=%f degrees, %f radians\r\n", pressureAngle, pressureAngleRadians);
    printf("dedendum=%f\r\n", dedendum);
    printf("teeth whole depth=%f\r\n", teethWholeDepth);

    printf("gear 1\r\n");
    printf("  root circle diameter (mm): %f\r\n", gear1RootCircleDiameter);
    printf("  base circle diameter (mm): %f\r\n", gear1BaseCircleDiameter);
    printf("  clearance circle diameter (mm): %f\r\n", gear1ClearanceCircleDiameter);
    printf("  pitch circle diameter (mm): %f\r\n", gear1PitchCircleDiameter);
    printf("  addendum circle diameter (mm): %f\r\n", gear1AddendumCircleDiameter);

    printf("gear 2\r\n");
    printf("  Number Of Teeth; Ratio; Diameter (mm)[Base, Root, Clearance, Pitch, Addendum]\r\n");

    for (float gear2NumberOfTeeth = gear1NumberOfTeeth; gear2NumberOfTeeth >= 6; gear2NumberOfTeeth--)
    {
        float gearRatio = gear1NumberOfTeeth / gear2NumberOfTeeth;
        float gear2PitchCircleDiameter = module * gear2NumberOfTeeth;
        float gear2AddendumCircleDiameter = gear2PitchCircleDiameter + 2 * module;
        float gear2RootCircleDiameter = gear2PitchCircleDiameter - 2 * dedendum;
        float gear2ClearanceCircleDiameter = gear2PitchCircleDiameter - 2 * module;
        float gear2BaseCircleDiameter = gear2PitchCircleDiameter * cosOfPressureAndleRadians;

        printf("  %f; %f; [%f, %f, %f, %f, %f]\r\n",
            gear2NumberOfTeeth,
            gearRatio,
            gear2BaseCircleDiameter, gear2RootCircleDiameter, gear2ClearanceCircleDiameter,
            gear2PitchCircleDiameter, gear2AddendumCircleDiameter);
    }
}

static void calculateGearsWithFixedDistance(float shaftDistance, float module, float pressureAngle)
{
    float gear1NumberOfTeeth = 0;
    float gear2NumberOfTeeth = 0;

    float totalNumberOfTeeth = shaftDistance * 2 / module;

    if ((int)totalNumberOfTeeth != totalNumberOfTeeth)
    {
        printf("Adjusting module.\r\n");
        totalNumberOfTeeth = (float)(int)(totalNumberOfTeeth);
        module = shaftDistance * 2 / totalNumberOfTeeth;
    }

    float dedendum = 1.25 * module;
    float teethWholeDepth = module + dedendum;
    float pressureAngleRadians = M_PI * pressureAngle / 180;
    double cosOfPressureAndleRadians = cos((double)pressureAngleRadians);

    printf("module=%f\r\n", module);
    printf("totalNumberOfTeeth=%f\r\n", totalNumberOfTeeth);
    printf("pressure angle=%f degrees, %f radians\r\n", pressureAngle, pressureAngleRadians);
    printf("dedendum=%f\r\n", dedendum);
    printf("teeth whole depth=%f\r\n", teethWholeDepth);

    printf("Ratio; Number Of Teeth; Diameter (mm)[Base, Root, Clearance, Pitch, Addendum]\r\n");

    for (gear1NumberOfTeeth = 6, gear2NumberOfTeeth = totalNumberOfTeeth - 6;
         gear2NumberOfTeeth >= 6;
         gear1NumberOfTeeth++, gear2NumberOfTeeth--)
    {
        float gearRatio = gear1NumberOfTeeth / gear2NumberOfTeeth;

        float gear1PitchCircleDiameter = module * gear1NumberOfTeeth;
        float gear1AddendumCircleDiameter = gear1PitchCircleDiameter + 2 * module;
        float gear1RootCircleDiameter = gear1PitchCircleDiameter - 2 * dedendum;
        float gear1ClearanceCircleDiameter = gear1PitchCircleDiameter - 2 * module;
        float gear1BaseCircleDiameter = gear1PitchCircleDiameter * cosOfPressureAndleRadians;

        float gear2PitchCircleDiameter = module * gear2NumberOfTeeth;
        float gear2AddendumCircleDiameter = gear2PitchCircleDiameter + 2 * module;
        float gear2RootCircleDiameter = gear2PitchCircleDiameter - 2 * dedendum;
        float gear2ClearanceCircleDiameter = gear2PitchCircleDiameter - 2 * module;
        float gear2BaseCircleDiameter = gear2PitchCircleDiameter * cosOfPressureAndleRadians;

        printf("%f; 1:%f, [%f, %f, %f, %f, %f], 2:%f, [%f, %f, %f, %f, %f]\r\n",
            gearRatio,
            gear1NumberOfTeeth,
            gear1BaseCircleDiameter, gear1RootCircleDiameter, gear1ClearanceCircleDiameter,
            gear1PitchCircleDiameter, gear1AddendumCircleDiameter,
            gear2NumberOfTeeth,
            gear2BaseCircleDiameter, gear2RootCircleDiameter, gear2ClearanceCircleDiameter,
            gear2PitchCircleDiameter, gear2AddendumCircleDiameter);
    }
}

int main(int argc, const char** argvd)
{
    // ./main ra 107.95 120.65 20
    const char* argv[5];
    argv[0] = "./main";
    argv[1] = "ra";
    argv[2] = "107.95";
    argv[3] = "120.65";
    argv[4] = "20";

    if (strncmp(argv[1], "ra", 2) == 0)
    {
        float gear1RootCircleDiameter = atof(argv[2]);
        float gear1AddendumCircleDiameter = atof(argv[3]);
        float pressureAngle = atof(argv[4]); // Standard: 20 degrees.

        calculateGearsWithFixedAddendum(
            gear1RootCircleDiameter, gear1AddendumCircleDiameter, pressureAngle);
    }
    else if (strncmp(argv[1], "d", 1) == 0)
    {
        float module = atof(argv[2]);
        float gearRatio = atof(argv[3]);
        float shaftDistance = atof(argv[4]);
        float pressureAngle = atof(argv[5]); // Standard: 20 degrees.

        calculateGearsWithFixedDistance(shaftDistance, module, pressureAngle);
    }
    else
    {
        printf("Unknown option.\r\n");
    }

    return 0;
}


