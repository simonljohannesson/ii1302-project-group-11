import { mount } from '@vue/test-utils'
import Welcome from './../../src/views/Welcome'
test('Welcome component text exist', () => {
    const wrapper = mount(Welcome)    
    expect(wrapper.html()).toContain('Welcome to Body Count!')
})
test('Welcome component does not contain about text', () => {
    const wrapper = mount(Welcome);
    expect(wrapper.html()).not.toContain('About')
})