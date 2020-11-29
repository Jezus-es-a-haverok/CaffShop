from django.test import TestCase, Client
from django.urls import reverse

# Create your tests here.

class BaseTest(TestCase):
    def setUp(self):
        self.register_url = reverse('register')
        self.user = {
            'username': 'test_user',
            'email': 'test@test.com',
            'password1': 'TestPassword_1',
            'password2': 'TestPassword_1'
        }
        self.user_short_password = {
            'username': 'test_user',
            'email': 'test@test.com',
            'password1': 'TstPw_1',
            'password2': 'TstPw_1'
        }
        self.user_password_too_similar = {
            'username': 'test_user',
            'email': 'TestPassword_1@test.com',
            'password1': 'TestPassword_1',
            'password2': 'TestPassword_1'
        }
        self.user_password_no_digit = {
            'username': 'test_user',
            'email': 'TestPassword_1@test.com',
            'password1': 'Test_Password',
            'password2': 'Test_Password'
        }
        self.user_password_no_uppercase = {
            'username': 'test_user',
            'email': 'test@test.com',
            'password1': 'testpassword_1',
            'password2': 'testpassword_1'
        }
        self.user_password_no_lowercase = {
            'username': 'test_user',
            'email': 'test@test.com',
            'password1': 'TESTPASSWORD_1',
            'password2': 'TESTPASSWORD_1'
        }
        self.user_password_no_symbol = {
            'username': 'test_user',
            'email': 'test@test.com',
            'password1': 'TestPassword1',
            'password2': 'TestPassword1'
        }
        return super().setUp()

class RegisterTest(BaseTest):
    def test_can_view_page_correctly(self):
        response = self.client.get(self.register_url)
        self.assertEqual(response.status_code, 200) 
        self.assertTemplateUsed(response, 'register/register.html')
    
    def test_register_success(self):
        response = self.client.post(self.register_url, self.user, format='text/html')
        self.assertEqual(response.status_code, 302) # 302 - redirected to /login - SUCCESS

    def test_register_fail_username_taken(self):
        self.client.post(self.register_url, self.user, format='text/html')
        response = self.client.post(self.register_url, self.user, format='text/html')
        self.assertEqual(response.status_code, 200) # 200 - stayed at the same endpoint - FAIL
        self.assertTemplateUsed(response, 'register/register.html')

    def test_register_fail_short_password(self):
        response = self.client.post(self.register_url, self.user_short_password, format='text/html')
        self.assertEqual(response.status_code, 200) # 200 - stayed at the same endpoint - FAIL
        self.assertTemplateUsed(response, 'register/register.html')

    def test_register_fail_password_too_similar(self):
        response = self.client.post(self.register_url, self.user_password_too_similar, format='text/html')
        self.assertEqual(response.status_code, 200) # 200 - stayed at the same endpoint - FAIL
        self.assertTemplateUsed(response, 'register/register.html')

    def test_register_fail_password_no_digit(self):
        response = self.client.post(self.register_url, self.user_password_no_digit, format='text/html')
        self.assertEqual(response.status_code, 200) # 200 - stayed at the same endpoint - FAIL
        self.assertTemplateUsed(response, 'register/register.html')

    def test_register_fail_password_no_uppercase(self):
        response = self.client.post(self.register_url, self.user_password_no_uppercase, format='text/html')
        self.assertEqual(response.status_code, 200) # 200 - stayed at the same endpoint - FAIL
        self.assertTemplateUsed(response, 'register/register.html')

    def test_register_fail_password_no_lowercase(self):
        response = self.client.post(self.register_url, self.user_password_no_lowercase, format='text/html')
        self.assertEqual(response.status_code, 200) # 200 - stayed at the same endpoint - FAIL
        self.assertTemplateUsed(response, 'register/register.html')

    def test_register_fail_password_no_symbol(self):
        response = self.client.post(self.register_url, self.user_password_no_symbol, format='text/html')
        self.assertEqual(response.status_code, 200) # 200 - stayed at the same endpoint - FAIL
        self.assertTemplateUsed(response, 'register/register.html')
