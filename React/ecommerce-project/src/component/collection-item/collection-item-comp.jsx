import React from 'react'
import './collection-item-styles.scss'

function collectionItemComp({id, name, price, imageUrl}) {
    return (
        <div className='collection-item'>
            <div className='image'
             style={{ backgroundImage: `url(${imageUrl})`}}
            >

            </div>
        </div>
    )
}

export default collectionItemComp
