/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2013-2016 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "volFields.H"

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CompType, class SolidThermo>
inline Foam::PtrList<Foam::DimensionedField<Foam::scalar, Foam::volMesh>>&
Foam::solidChemistryModel<CompType, SolidThermo>::RRs()
{
    return RRs_;
}

template<class CompType, class SolidThermo>
inline const Foam::PtrList<Foam::Reaction<SolidThermo>>&
Foam::solidChemistryModel<CompType, SolidThermo>::reactions() const
{
    return reactions_;
}


template<class CompType, class SolidThermo>
inline Foam::label
Foam::solidChemistryModel<CompType, SolidThermo>::
nReaction() const
{
    return nReaction_;
}


template<class CompType, class SolidThermo>
inline const Foam::DimensionedField<Foam::scalar, Foam::volMesh>&
Foam::solidChemistryModel<CompType, SolidThermo>::RRs
(
    const label i
) const
{
    return RRs_[i];
}


template<class CompType, class SolidThermo>
inline Foam::tmp<Foam::DimensionedField<Foam::scalar, Foam::volMesh>>
Foam::solidChemistryModel<CompType, SolidThermo>::RRs() const
{
    tmp<DimensionedField<scalar, volMesh>> tRRs
    (
        new DimensionedField<scalar, volMesh>
        (
            IOobject
            (
                "RRs",
                this->time().timeName(),
                this->mesh(),
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            this->mesh(),
            dimensionedScalar("zero", dimMass/dimVolume/dimTime, 0.0)
        )
    );

    if (this->chemistry_)
    {
        DimensionedField<scalar, volMesh>& RRs = tRRs.ref();
        for (label i=0; i < nSolids_; i++)
        {
            RRs += RRs_[i];
        }
    }
    return tRRs;
}


// ************************************************************************* //
