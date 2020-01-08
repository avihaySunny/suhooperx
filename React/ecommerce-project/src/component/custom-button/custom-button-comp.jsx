import React from 'react'
import './custom-button-styles.scss'

function CustomButton(props){
    const {children,...otherProps}= props
    return ( 
    <button className='custom-button'{...otherProps}> 
        {children}
       </button>
    ) 
}

export default CustomButton
