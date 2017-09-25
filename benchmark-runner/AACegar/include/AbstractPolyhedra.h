//Authors: Dario Cattaruzza, Alessandro Abate, Peter Schrammel, Daniel Kroening
//University of Oxford 2016
//This code is supplied under the BSD license agreement (see license.txt)

#ifndef ABSTRACT_POLYHEDRA_H
#define ABSTRACT_POLYHEDRA_H

#include <limits>
#include <stdlib.h>

#include "Polyhedra.h"

namespace abstract
{

template <class scalar> class AbstractPolyhedra : public Polyhedra<scalar>
{
public:
    using typename Tableau<scalar>::refScalar;
    using typename Tableau<scalar>::type;
    using typename Tableau<scalar>::func;
    using typename Tableau<scalar>::MatrixS;
    typedef typename type::sparseMatrix SMatrixS;
    typedef typename type::sparseVector sparseVector;
    typedef typename type::iteration_pair iteration_pair;

    using Tableau<scalar>::m_faces;
    using Tableau<scalar>::m_supports;
    using Polyhedra<scalar>::m_vertices;
    using Polyhedra<scalar>::m_centre;
    using Tableau<scalar>::ms_logger;
    using Polyhedra<scalar>::ms_emptyMatrix;

    using Tableau<scalar>::getDimension;
    using DualSimplex<scalar>::findRedundancies;
    using Polyhedra<scalar>::load;
    using Polyhedra<scalar>::addDirection;
    using Polyhedra<scalar>::getVertices;
    using Polyhedra<scalar>::getName;
    using Polyhedra<scalar>::centralize;
    using Polyhedra<scalar>::decentralize;
    using Polyhedra<scalar>::translate;
    using Polyhedra<scalar>::makeVertices;
    using Polyhedra<scalar>::boundingHyperBox;

    /// Constructs an empty buffer
    /// @param dimension dimension of the space
    AbstractPolyhedra(int dimension=0,bool sparse=false);

    /// Constructs transformed polyhedra
    /// @param source template to copy to create this polyhedra
    /// @param transform transformation matrix to obtain this polyhedra
    /// @param inverse precalculated inverse of transform
    AbstractPolyhedra(const AbstractPolyhedra& source,const MatrixS &transform=ms_emptyMatrix,const MatrixS &inverse=ms_emptyMatrix);

    /// Retrieves the corresponding circular vectors for a given set of vectors
    /// @param roundings marks the variables to fold
    MatrixS getRoundedDirections(const MatrixS &vectors,const std::vector<int> &roundings);

    /// Retrieves an abstraction that has circular faces in the rotating axis and jordan blocks
    /// @return true if there are circular faces in the abstraction
    bool getRoundAbstraction(int dimension,int roundDimension,const std::vector<int> &roundings,AbstractPolyhedra<scalar> &roundAbstraction);

    /// Retrieves an abstraction that has circular faces along the rotating axis and jordan blocks
    /// @param roundings variables to fold (set as indexof beginning of block)
    AbstractPolyhedra& getRounded(const std::vector<int> &roundings,AbstractPolyhedra &roundAbstraction,bool preCentralized=false);

    /// Retrieves an abstraction that has circular faces in the rotating axis and jordan blocks
    /// @return true if there are circular faces in the abstraction
    bool getSquareAbstraction(AbstractPolyhedra<scalar> &squareAbstraction,bool symmetric);

    /// Performs the Minkowski sum of this polyhedra to another
    /// @param polyhedra polyhedra to merge
    /// @param roundings variables to be folded in the polyhedra
    /// @return true if successful
    bool addRounded(Polyhedra<scalar> &polyhedra,const std::vector<int> &roundings);

    /// Retrives the vertices mapped into an abstract domain of a linear matrix
    /// @param rotations rotating axis represented by a single vector in the added polyhedra
    /// @param dilations dilating axis represented by a single vector in the added polyhedra
    MatrixS getAbstractVertices(MatrixS &vector,const int row,const std::vector<int> &rotations,const std::vector<int> &dilations,const MatrixS &vertices);
    MatrixS getAbstractVertices(MatrixS &vector,const int row,const std::vector<int> &rotations,const std::vector<int> &dilations)
    { return getAbstractVertices(vector,row,rotations,dilations,getVertices()); }

    /// Retrives the vertices mapped into an abstract domain of a linear matrix
    /// @param vectors directions to merge the vertices with
    /// @param rotations rotating axis represented by a single vector in the added polyhedra
    /// @param dilations dilating axis represented by a single vector in the added polyhedra
    MatrixS getAbstractVertices(const MatrixS &vectors,const std::vector<int> &rotations,const std::vector<int> &dilations,const MatrixS &vertices);
    MatrixS getAbstractVertices(const MatrixS &vectors,const std::vector<int> &rotations,const std::vector<int> &dilations)
    { return getAbstractVertices(vectors,rotations,dilations,getVertices()); }

    /// Sets the vertices of the polyhedra from a precalculated set
    /// @param vertices precalculated vertices
    /// @param centre if not empty, indicates a translation point to centralize the polyhedra
    bool setVertices(MatrixS &vertices,const MatrixS &centre=ms_emptyMatrix);

    /// Retrives the vertices mapped into an abstract domain of a linear matrix
    /// @param vectors directions to merge the vertices with
    /// @param rotations rotating axis represented by a single vector in the added polyhedra
    /// @param dilations dilating axis represented by a single vector in the added polyhedra
    MatrixS getSynthVertices(const MatrixS &vectors,const std::vector<int> &rotations,const std::vector<int> &dilations,const std::vector<int> &roundings,const MatrixS &vertices);
    MatrixS getSynthVertices(const MatrixS &vectors,const std::vector<int> &rotations,const std::vector<int> &dilations,const std::vector<int> &roundings)
    { return getSynthVertices(vectors,rotations,dilations,roundings,getVertices()); }

    /// Retrieves a copy of this polyhedra transformed by the given matrix
    /// @param pTransform transform matrix
    /// @param pInverse inverse of transform matrix
    /// @param pPolyhedra container for the result (if NULL, a new one is created)
    AbstractPolyhedra& getTransformedPolyhedra(Polyhedra<scalar>& polyhedra,const MatrixS& transform,const MatrixS& inverse=Polyhedra<scalar>::ms_emptyMatrix,const MatrixS &templates=Polyhedra<scalar>::ms_emptyMatrix);
    AbstractPolyhedra& getTransformedPolyhedra(const MatrixS& transform,const MatrixS& inverse=Polyhedra<scalar>::ms_emptyMatrix,const MatrixS &templates=Polyhedra<scalar>::ms_emptyMatrix)
    { return getTransformedPolyhedra(*(new AbstractPolyhedra(this->getDimension())),transform,inverse,templates); }

    /// Retrieves a slice of the polyhedra for the size dimensions starting at offset
    /// Extra dimensions are assumed to be at origin
    /// @param size number of dimensions to extract
    /// @param offset dimension to start the slice on
    bool slice(AbstractPolyhedra<scalar>&target,int size,int offset=0,int rowSize=0,int rowOffset=0);

    /// Retrieves a 2D slice of the polyhedra for the given variable pair centered at centre
    bool getPlane(AbstractPolyhedra<scalar>&target,int col1,int col2,MatrixS &centre);

    /// Clears redundant faces in the polyhedra (caused by intersections and reductions)
    /// @return true if successful
    virtual bool removeRedundancies();

    /// Loads a description into the tableau (Ax<b)
    /// @param faces (A-Matrix) normal to the half-spaces describing the problem
    /// @param supports (b-vector) boundaries of the half-spaces (given as support functions)
    /// @param iterations list of iteration-row tags for the directions
    /// @param transpose, directions are col vectors when true and row vectors when false
    /// @return false if failed
    bool loadTagged(const MatrixS &faces,const MatrixS &supports,std::vector<iteration_pair> &iterations,const bool transpose=false);

    /// Adds a number of directions to the template of the polhedra
    /// @param directions column vectors to add
    /// @param supports support vectors of the polyhedra in the given directions (when known)
    /// @param iterations list of iteration-row tags for the directions
    /// @param keepBasis if true does not remove redundacies in order to keep the active tableau current.
    /// @return true if successful
    bool addTaggedDirection(const MatrixS &directions,MatrixS &supports,std::vector<iteration_pair>  &iterations,bool keepBasis=false);

    /// Loads a description into the tableau (Ax<b)
    /// @param faces (A-Matrix) normal to the half-spaces describing the problem
    /// @param supports (b-vector) boundaries of the half-spaces (given as support functions)
    /// @param iterations list of iteration-row tags for the directions
    /// @return false if failed
    bool loadTagged(SMatrixS &faces,const MatrixS &supports,std::vector<iteration_pair> &iterations);

    /// Adds a number of directions to the template of the polhedra
    /// @param directions column vectors to add
    /// @param supports support vectors of the polyhedra in the given directions (when known)
    /// @param iterations list of iteration-row tags for the directions
    /// @param keepBasis if true does not remove redundacies in order to keep the active tableau current.
    /// @return true if successful
    bool addTaggedDirection(SMatrixS &faces,MatrixS &supports,std::vector<iteration_pair>  &iterations,bool keepBasis=false);

public:
    std::vector<iteration_pair> m_iterations;
    static bool                 ms_trace_abstraction;

};

}

#endif //ABSTRACT_POLYHEDRA_H
