// Fill out your copyright notice in the Description page of Project Settings.

#include "math.h" 
#include "Calculatriz.h"

float UCalculatriz::GetBounceAngle(FVector Alpha,FVector Beta)
{
    
    //Angulo de entrada
    float Teta=GetVectorsAngle(Alpha,Beta);
    float Sense=1;
    if(Beta.X<=0 && Beta.X>-1){Beta.X=-Beta.Y;}else if(Beta.Y<=0 && Beta.Y>-1){Beta.Y=Beta.X;}
    //UE_LOG(LogTemp, Warning, TEXT("(%f,%f)"),Beta.X,Beta.Y )

    if(-Beta.X/Alpha.X<0){
        Sense=-1;
	    //UE_LOG(LogTemp, Warning, TEXT("UE_LO a vino X") )
    }
    if(-Beta.Y/Alpha.Y<0){
        Sense=-1;
	    //UE_LOG(LogTemp, Warning, TEXT("UE_LO a vino Y") )
    }
    float Zeta=180-Teta;
    float Epsilon=(Teta-Zeta)*Sense;
	//UE_LOG(LogTemp, Warning, TEXT("ImpactAngle --> %f"),Teta )
	//UE_LOG(LogTemp, Warning, TEXT("ImoactAngleV2 --> %f"),Zeta ) 
	//UE_LOG(LogTemp, Warning, TEXT("RotationBounce --> %f"),Epsilon )

    return Epsilon;
}

float UCalculatriz::GetVectorsAngle(FVector Alpha,FVector Beta)
{   
    return acos(
            DotProduct(Alpha,Beta)/
            (GetVectorMagnitude(Alpha)*GetVectorMagnitude(Beta))
        )*180/3.1415;
}

double UCalculatriz::DotProduct(FVector A,FVector B)
{
    return (A.X*B.X+A.Y*B.Y+A.Z*B.Z);
}

double UCalculatriz::GetVectorMagnitude(FVector Vector3D)
{
    double x=Vector3D.X;
    double y=Vector3D.Y;
    double z=Vector3D.Z;
	//UE_LOG(LogTemp, Warning, TEXT("Vector--> ( %f , %f , %f )"),x,y,z );

    return sqrt(x*x+y*y+z*z);
}

