import React from 'react'
import './signinpage-styles.scss'
import SingIn from '../../component/signin/signin-comp'
import SignUp from '../../component/sign-up/sign-up-comp'

const SignInPage = () =>(
    <div className='signinpage'>
        <SingIn/>
        <SignUp/>
    </div>
)

export default SignInPage