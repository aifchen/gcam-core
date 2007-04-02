/* xml_pair.h
 * Created: 03/09/2007
 * Version: 03/09/2007
 *
 * This software, which is provided in confidence, was prepared by employees
 * of Pacific Northwest National Laboratory operated by Battelle Memorial
 * Institute. Battelle has certain unperfected rights in the software
 * which should not be copied or otherwise disseminated outside your
 * organization without the express written authorization from Battelle.
 * All rights to the software are reserved by Battelle.   Battelle makes no
 * warranty, express or implied, and assumes no liability or responsibility
 * for the use of this software.
 */

#if !defined( XML_PAIR_H )
#define XML_PAIR_H         // prevent multiple includes

// include files ***********************************************************

#include "util/base/include/xml_helper.h"
#include <string>

// namespaces **************************************************************

namespace ObjECTS {

// class: XMLPair **********************************************************

/*! \ingroup Objects
 *  \brief XMLPair<T> is a class template for a XML <key, value> pair
 *  \details The class template XMLPair<T> is used to the <key, value> pair
 *           of a named XML element that contains a value.
 * 
 *  \author Kevin Walker
 * \date $ Date $
 * \version $ Revision $
 */
template <class T = std::string>
class XMLPair
{
public :

   typedef T value_type;

   /*! Default constructor
    *  \param aKey the key (optional)
    *  \param aValue the value (optional)
    */
   XMLPair(
      const std::string& aKey = std::string(),
      const value_type&  aValue = value_type() )
      : mKey( aKey ), mValue( aValue ) {}
   /*! Copy constructor
    *  \param other the instance to copy
    */
   XMLPair( const XMLPair<T>& other )
      : mKey( other.mKey ), mValue( other.mValue ) {}
   /*! Copy from a STL pair
    *  \param aPair the pair to copy
    */
   XMLPair( const std::pair<std::string, value_type>& aPair )
      : mKey( aPair.first ), mValue( aPair.second ) {}

   /*! Assignment operator
    *  \param other the instance to copy
    *  \return *this
    */
   XMLPair<T>& operator = ( const XMLPair<T>& other )
   {
      if ( &other != this )
      {
         mKey   = other.mKey;
         mValue = other.mValue;
      }
      return *this;
   }
   /*! Assignment operator
    *  \param aPair the pair to copy
    *  \return *this
    */
   XMLPair<T>& operator = ( const std::pair<std::string, value_type>& aPair )
   {
      mKey   = aPair.first;
      mValue = aPair.second;
      return *this;
   }

    /*! Add this to the specified node
    *  \param apNode the parent node
    *  \return true on success, false otherwise
    */
   virtual bool generate( xercesc::DOMNode * apNode );

   /*! Get the key
    *  \return the key
    */
   virtual const std::string& getKey( void ) const { return mKey; }

   /*! Get the value
    *  \return the value
    */
   virtual const value_type& getValue( void ) const { return mValue; }

    /*! Parse a pair from the specified node
    *  \param apNode the node to parse
    *  \return true on success, false otherwise
    */
   virtual bool parse( const xercesc::DOMNode * apNode );

   /*! Print to the specified output stream
    *  \param out the output stream
    *  \param apTabs the current tab setting
    *  \return the output stream
    */
   virtual std::ostream& print( std::ostream& out, Tabs * apTabs = 0 );

   /*! Set the key
    *  \param aKey the key to set
    */
   virtual void setKey( const std::string& aKey ) { mKey = aKey; }

   /*! Set the value
    *  \param aValue the value to set
    */
   virtual void setValue( const value_type& aValue ) { mValue = aValue; }

private :

   //! The key/name for the pair
   std::string mKey;
   //! The value for the pair
   value_type  mValue;
};

// XMLPair<T>::generate ****************************************************

 /*! Add this to the specified node
 *  \param apNode the parent node
 *  \return true on success, false otherwise
 */
template <class T>
inline bool XMLPair<T>::generate( xercesc::DOMNode * apNode )
{
   // Validate the node
   if ( !apNode || apNode->getNodeType() != xercesc::DOMNode::ELEMENT_NODE )
   {
      return false;
   }
   // TODO

   return true;
}

// XMLPair<T>::parse *******************************************************

 /*! Parse a pair from the specified node
 *  \param apNode the node to parse
 *  \return true on success, false otherwise
 */
template <class T>
inline bool XMLPair<T>::parse( const xercesc::DOMNode * apNode )
{
   // Validate the node
   if ( !apNode || apNode->getNodeType() != xercesc::DOMNode::ELEMENT_NODE )
   {
      return false;
   }

   // Get the node name (key)
   setKey( XMLHelper<string>::safeTranscode( apNode->getNodeName() ) );

   // Get the node value
   try
   {
      setValue( XMLHelper<T>::getValue( apNode ) );
      return true;
   }
   catch ( ... )
   {
   	return false;
   }
}

// XMLPair<T>::print *******************************************************

/*! Print to the specified output stream
 *  \param out the output stream
 *  \param apTabs the current tab setting
 *  \return the output stream
 */
template <class T>
inline std::ostream& XMLPair<T>::print(
   std::ostream& out,
   Tabs *        apTabs )
{
   XMLWriteElement( getValue(), getKey(), out, apTabs );
   return out;
}

} // namespace ObjECTS

#endif   // XML_PAIR_H

// end of xml_pair.h *******************************************************

