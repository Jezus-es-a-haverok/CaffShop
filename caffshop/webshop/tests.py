from datetime import date

from django.core.files.base import ContentFile
from django.test import TestCase, Client
from django.urls import reverse

from webshop.models import Comment, CAFF
from django.contrib.auth.models import User
from webshop.forms import UploadCAFFForm
from register.forms import RegisterForm
from django.core.files.uploadedfile import SimpleUploadedFile, TemporaryUploadedFile
# Create your tests here.

class CommentTestCase(TestCase):
    def setUp(self):
        Comment.objects.create(text="valami")
        Comment.objects.create(text="valami")
        Comment.objects.create(text="valami2")

    def test_multiple_get(self):
        flag = False
        try:
            valami = Comment.objects.get(text="valami")
        except:
            flag = True
        finally:
            self.assertEqual(flag, True)

    def test_single_get(self):
        valami2 = Comment.objects.get(text="valami2")
        self.assertEqual("valami2", valami2.text)
        self.assertEqual(date.today(), valami2.date)
        self.assertIsNone(valami2.user)
        self.assertIsNone(valami2.image)


class UserTestCase(TestCase):

    def test_create_user(self):
        user = User.objects.create_user(username='john',
                                        email='jlennon@beatles.com',
                                        password='glass onion')
        self.assertEqual(user.username, "john")
        self.assertEqual(user.email, "jlennon@beatles.com")
        self.assertNotEqual(user.password, 'glass onion')

    def test_create_same_usernames(self):
        user = User.objects.create_user(username='john',
                                        email='jlennon@beatles.com',
                                        password='glass onion')
        flag = False
        try:
            user2 = User.objects.create_user(username='john',
                                             email='jlennon@beatles.com',
                                             password='glass onion')
        except:
            flag = True
        finally:
            self.assertEqual(flag, True)


class CAFFTestCase(TestCase):
    def setUp(self):
        self.user = User.objects.create_user(username='john',
                                        email='jlennon@beatles.com',
                                        password='glass onion')
        self.caff = CAFF.objects.create(user=self.user)



    def test_create_caff_user(self):
        self.assertEqual(self.caff.user, self.user)

# class UploadCAFFFormTestCase(TestCase):
#
#     def setUp(self):
#         self.content = open("example/2.caff", "rb")
#         self.uploaded_file = SimpleUploadedFile("example/2.caff", self.content.read())
#
#     def test_forms_empty_content(self):
#         form_data = {'name': 'valami'}
#         form = UploadCAFFForm(data=form_data)
#         self.assertFalse(form.is_valid())
#     #
#     # def test_forms_empty_name(self):
#     #     form_data = {'content': self.content}
#     #     form = UploadCAFFForm(data=form_data)
#     #     self.assertFalse(form.is_valid())
#     #
#     def test_forms_valid(self):
#         form_data = {'name': 'valami', 'content': self.content}
#         form = UploadCAFFForm(data=form_data)
#         self.assertTrue(form.is_valid())
#     #
#     # def test_form_response(self):
#     #     user = User.objects.create_user(username='admin',
#     #                                     password='admin')
#     #     c = Client()  # above, from django.test import TestCase,Client
#     #
#     #     response = c.post('/login/', {'username':'admin','password':'asd'})
#     #     print(response.status_code)
#     #     # with open("example/2.caff", "rb") as fp:
#     #     #
#     #     #     response = c.post('/webshop/upload/', {'content': fp})
#     #     #     print(response.context)
#
#
#         # response = self.client.get('/login/')
#         # csrf_token = response.context['csrf_token']
#         # print(csrf_token)
#         # response = self.client.post('/login/', {'username': 'admin', 'password': "admin", "csrfmiddlewaretoken": csrf_token})
#         # print(response.context)
#         # with open("example/2.caff", "rb") as fp:
#         #     response = self.client.post('/webshop/upload/', {'name': 'valami', 'content': fp})
#         # print(response)
#         # self.assertEqual(response.status_code, 200)


class LoginViewTestCase(TestCase):

    def test_login_valid(self):
        user = User.objects.create_user(username='admin',
                                        password='admin')
        c = Client()  # above, from django.test import TestCase,Client

        response = c.post('/login/', {'username': 'admin', 'password': 'admin'})
        self.assertEqual(response.status_code, 302)

    def test_login_not_valid(self):
        user = User.objects.create_user(username='admin',
                                        password='admin')
        c = Client()  # above, from django.test import TestCase,Client

        response = c.post('/login/', {'username': 'admin', 'password': 'asd'})
        self.assertEqual(response.status_code, 200)
